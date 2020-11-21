#ifndef _ITEM_HH
#define _ITEM_HH

class Item {
    public:
        Item(const char c);
        virtual ~Item();
        virtual void DoAction(void) const = 0;
        char GetRepr(void) const;

    private:
        char _char;
};

#endif
