using namespace std;

template<typename STATE, typename SYMBOL>
class dfa_t
{
public:
    struct transition_t
    {
        STATE   from_state;
        SYMBOL  input;
        STATE   to_state;
        std::function(void()) fn;
    };

    dfa_t();
    ~dfa_t();

    bool transtion(const STATE from, const SYMBOL input, STATE& to);

    bool set_transtion_matrix(transition_t* matrix, int count);

protected:
    bool find_transtion_(const STATE from, const SYMBOL input, transition_t& trans);

private:
    transition_t* matrix_;    // order by from_state
    int count_;
};

