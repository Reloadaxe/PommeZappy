#ifndef _ITEM_HH
#define _ITEM_HH

class Item {
    public:
        Item(const char c);
        virtual void DoAction(void) const = 0;
        const char GetChar(void) const;

    private:
        char _char;
}

#endif