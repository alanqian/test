#!/usr/bin/ruby

require 'yaml'
require 'logger'
require "fileutils"
require 'rubygems'
require 'mysql2'

class NewLogger
    attr_accessor :logger
    def initialize(logger)
        @logger = logger
    end

    %w{debug info warn error fatal}.each do |method|
        eval(<<-eomethod)
            def #{method}(msg)
                @logger.#{method}(position) {msg}
            end
        eomethod
    end

    private
    def position
        caller.at(1).sub(%r{.*/},'').sub(%r{:in\s.*},'')
    end
end

SQL_MAX_ID = "SELECT max(id) FROM "
LOGGER = NewLogger.new Logger.new(STDOUT)
LOGGER.logger.level = Logger::DEBUG

# curl -O http://repo1.maven.org/maven2/org/jruby/jruby-complete/1.1.1/jruby-complete-1.1.1.jar
class UserPosts
    def initialize(shard)
        @shard = shard
        @user2url = Hash.new()
        @url2user = Hash.new()
        @ts = 0
    end

    # don't use time_created in this version
    def add(user_id, md5, time_created, time_updated)
        @user2url[user_id] ||= []
        @user2url[user_id].push(md5)
        @url2user[md5] ||= []
        @url2user[md5].push(user_id)
        @ts = time_updated if @ts < time_updated
    end

    def output_user_saved_urls(filename)
        fd = File.new(filename, "w")
        count = 0
        @user2url.each do |k, v|
            v.uniq!
            fd.puts "#{k}\tposts:#{@shard}\t#{v.join(',')}\t#{@ts}\tpost_cnts:#{@shard}\t#{v.length}\t#{@ts}"
            count += 1
            # put(rowkey => user_id, qualifier => "posts:N", value => "md5 list", timestamp => "time_updated")
            # put(rowkey => user_id, qualifier => "posts_cnt:N", value => "posts_count", timestamp => "time_updated")
            # N is shard number
        end
        LOGGER.info("output user_saved_links to file, count:#{count} file:#{filename}")
        fd.close
    end

    # deprecated
    def output_url_savers(filename)
        fd = File.new(filename, "w")
        count = 0
        @url2user.each do |k, v|
            v.uniq!
            fd.puts "#{k}\tsavers\t#{v.join(',')}\t#{@ts}"
            count += 1
        end
        LOGGER.info("output url_savers to file, count:#{count} file:#{filename}")
        fd.close
    end
end

def load_conf(conf)
    YAML::load(File.read(conf))
end

def store_conf(filename, conf)
    FileUtils.mv filename, filename+".orig"
    fd = File.new(filename, "w")
    fd.puts(conf.to_yaml)
    fd.close
end

def connect_mysql(conf)
    LOGGER.debug("connect to mysql, host:#{conf[:host]}")
    conn = Mysql2::Client.new(
        :host => conf[:host], :username => conf[:user],
        :password => conf[:passwd], :database => conf[:db], :encoding => 'utf8')
    rs = conn.query(SQL_MAX_ID + conf[:table], :as => :array)
    max_id = rs.first[0]
    LOGGER.debug("max_id retrieved, max_id:#{max_id}")
    return conn, max_id
end

def find_id_before_days(conn, max_id, before_days, estimated_daily_records)
    # find the proper start id which satisfy time_updated < this_time - before_days
    # Estimated daily posts = 50000
    sql = "SELECT time_updated FROM av_post WHERE id = #{max_id}"
    rs = conn.query(sql, :as => :array)
    this_time = rs.first[0]
    tail = this_time % 86400
    that_time = this_time - tail - before_days * 86400
    before_days += (tail / 86400.0)
    puts "before_days: #{before_days}"
    puts "that_time: #{that_time}"
    puts "this_time: #{this_time}"
    # 1/40, 1/38, 1/4, 1/2, 1, 1.5, ..., 20
    scales = 20.downto(2).map { |i| 0.5 / i }
    scales.concat(1.upto(40).map { |i| 0.5 * i })
    id_range = scales.map do |scale| 
        max_id - (scale * estimated_daily_records * before_days).floor
    end
    sql = "SELECT id,time_updated FROM av_post WHERE id IN (#{id_range.join(',')}) ORDER BY time_updated DESC"
    # puts "********DEBUG*********", sql
    rs = conn.query(sql, :as => :array)
    # rs.each { |r| puts r.join('|') }
    if rs.count
        # puts rs
        last = nil
        r = rs.find { |r| last = r; r[1].to_i < that_time }
        return r[0].to_i if r
        return last[0].to_i
    end
    # return nil
end

def test(conn, query, max_id, count)
    LOGGER.info("test mysql, conf: ${conf}")
    sql = query % { from: (max_id - count), to: max_id }
    LOGGER.debug("query mysql, sql:#{sql}")
    rs = conn.query(sql)
    LOGGER.info("query mysql, returns:#{rs.count} sql:#{sql}")
end

def load_mysql_data(conn, query, start, count)
    sql = query % { from: start, to: start + count }
    LOGGER.debug("query mysql, start:#{start} count:#{count} sql:#{sql}")
    rs = conn.query(sql)
    LOGGER.debug("query mysql returns, start:#{start} count:#{count} returns:#{rs.count} sql:#{sql}")
    rs
end

def put_data_to_file(rs, fields, filename)
    fd = File.new(filename, "w")
    rs.each(:as => :hash) { |row| fd.puts row.values_at(*fields).join("\t") }
    fd.close
    LOGGER.info("output to file, rows:#{rs.count} file:#{filename}")
end

def store_data_to_hbase(rb_script, datafile)
    LOGGER.info("system(hbase shell #{rb_script} #{datafile})")
    system("hbase shell #{rb_script} #{datafile}")
end

def store_data_to_hbase2(rb_script, datafile, datafile2)
    LOGGER.info("system(hbase shell #{rb_script} #{datafile} #{datafile2})")
    system("hbase shell #{rb_script} #{datafile} #{datafile2}")
end

def migrate(conf_file)
    begin
        conf = load_conf(conf_file)
        output = conf[:output]
        fields = conf[:fields]
        ruby_script = conf[:ruby_script]
        table = conf[:table]
        shard = conf[:shard]

        conn, max_id = connect_mysql(conf)
        start_id = find_id_before_days(conn, max_id, 150, 50000)
        puts "start: #{start_id}, count: #{max_id - start_id}"
        return
        query = conf[:query]

        batch_size = conf[:batch_size]

        test_size = conf[:test]
        test(conn, query, max_id, batch_size) if test_size > 0

        start = conf[:last_id]
        if start <= 0
            start = max_id - test_size if test_size > 0
        end

        LOGGER.info("start batches, conf:#{conf_file} start:#{start} max_id:#{max_id}")
        while start < max_id do
            LOGGER.info("start copying, conf:#{conf_file} start:#{start} max_id:#{max_id}")
            count = [max_id - start, batch_size].min
            rs = load_mysql_data(conn, query, start, count)

            if table.eql?("av_post")
                posts = UserPosts.new(shard)
                rs.each(:as => :hash) do |row|
                    user_id, md5, time_created, time_updated = row.values_at(*fields)
                    posts.add(user_id, md5, time_created.to_i, time_updated.to_i)
                end
                output_files = output.map { |o| o + start.to_s }
                posts.output_user_saved_urls(output_files[0])
                posts.output_url_savers(output_files[1])
                store_data_to_hbase2(ruby_script, *output_files)
            else
                output_file = output + start.to_s
                put_data_to_file(rs, fields, output_file)
                store_data_to_hbase(ruby_script, output_file)
            end

            start += count
            conf[:last_id] = start
            store_conf(conf_file, conf)
        end

    rescue Mysql2::Error => e
        LOGGER.fatal("mysql error, conf:#{conf}")
        LOGGER.warn(e)
    ensure
        conn.close if conn
    end
end

def main
    ARGV.each do |v|
        LOGGER.info("task start, conf:#{v}")
        migrate(v) if v and File.exists?(v)
        LOGGER.info("task completed, conf:#{v}")
    end
end
main

def make_confs
    conf = load_conf "avpost.0.yaml"
    av_post_hosts = [
        "user-0-master-b-c.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-1-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-2-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-3-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-4-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-5-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-6-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-7-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-8-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        "user-9-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com"
    ]
    puts conf[:query]
    0.upto(9) do |shard|
        file = "avpost.#{shard}.yaml"
        format = "/mnt/mysql2hbase/avpost/%s.#{shard}."
        conf[:host] = av_post_hosts[shard]
        conf[:output] = ["user-posts", "url-savers"].map { |name| format % name }
        conf[:shard] = shard
        conf[:batch_size] = 50000
        conf[:test] = 9000000
        store_conf(file, conf)
    end
end
#make_confs
exit

=begin
def load_default_conf
    # av_url_agg
    conf = {
        host: "urlagg-0-master-b.c6phkmp5c3yd.us-west-1.rds.amazonaws.com",
        # query % { from: *, to: }
        query: "SELECT url_md5, best_tags, best_title, first_saver_date, last_saver_date FROM av_url_agg WHERE id > %{from} AND id <= %{to}",
        user: "avos",
        passwd: "juic3juice",
        db: "av_url_agg",
        batch_size: 10000,
        last_id: -1,
        max_id: 100,
        test: 10000,
        fields: %w(url_md5 best_tags best_title),
        output: "/mnt/mysql2hbase/av_urlagg.",
        ruby_script: "put-avurlagg.rb",
        table: "av_url_agg",
        shard: nil
    }
    puts conf.to_yaml
    conf = {
        host: "leopard.mei.fm",
        user: "root",
        # query % { from: *, to: }
        query: "SELECT url_md5, best_tags, best_title, first_saver_date, last_saver_date FROM av_url_agg WHERE id > %{from} AND id <= %{to}",
        passwd: "bWy4$*5K",
        db: "urlagg",
        batch_size: 100,
        last_id: -1,
        max_id: 100,
        test: 10000,
        fields: %w(url_md5 best_tags best_title),
        output: "./av_urlagg.",
        ruby_script: "put-avurlagg.rb",
        table: "av_url_agg",
        shard: nil
    }
    puts conf.to_yaml
end
=end
