#ifndef _ITEM_HH
#define _ITEM_HH

class Item {
    public:
        Item(const char c);
        virtual ~Item();
        virtual void DoAction(void) = 0;
        char GetChar(void);

    private:
        char _char;
};

#endif
