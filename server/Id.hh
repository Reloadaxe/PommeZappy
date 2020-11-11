#ifndef _ID_HH
#define _ID_HH

class Id {
    public:
        Id(const Id&) = delete;
        Id& operator=(const Id&) = delete;
        static const unsigned int New(void);
    
    private:
        static unsigned int _id;
};

#endif