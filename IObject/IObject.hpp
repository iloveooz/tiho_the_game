#ifndef TIHO_IOBJECT_HPP
#define TIHO_IOBJECT_HPP

// абстрактный класс (интерфейс) для всех объектов
class IObject {
public:
    IObject();
    virtual ~IObject();

    static long getCounter();
    long getID() const;
private:
    static long counter;
    long ID;
};

#endif //TIHO_IOBJECT_HPP
