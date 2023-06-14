namespace pixel
{

template<typename T>
class queue {

    private:
        using value_type = T;
        using ptr_type = T*;
        
        using queue_type = queue<value_type>;
        using queue_ptr = queue<value_type>*;

    public:
        queue();
        ~queue();
    
        void operator = (queue)

};


}