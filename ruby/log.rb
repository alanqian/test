require 'logger'

def main
    logger = Logger.new(STDOUT)
    #logger.progname = __FILE__
    logger.formatter = proc do |severity, datetime, progname, msg|
        # caller.first(4)
        # 1,2: /usr/lib/ruby/1.9.1/logger.rb:491:in `call'
        # 3: /usr/lib/ruby/1.9.1/logger.rb:491:in `format_message'
        # 4: /usr/lib/ruby/1.9.1/logger.rb:378:in `add'
        # /usr/lib/ruby/1.9.1/logger.rb:399:in `debug'
        progname ||= caller[4]
        "#{datetime} #{severity} #{progname} - #{msg}\n"
    end
    logger.debug("debug log test")
    logger.close
end
main
