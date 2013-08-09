
class dump_buffer_t {
public:
    dump_buffer_t();
    virtual ~dump_buffer_t();

    virtual char* get_buffer(int length);
};

class foo
{
    const char* to_log(dump_buffer_t& dbuf);
    const char* to_string(dump_buffer_t& dbuf);
};


