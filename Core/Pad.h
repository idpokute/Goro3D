#ifndef __PAD_H__
#define __PAD_H__

class Pad {
public:
    enum Button {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        JUMP,
        FIRE1,
    };

    static Pad* Instance();
    static void Create();
    static void Destroy();

    bool isOn(Button, int id) const;
    bool isTriggered(Button, int id) const;

private:
    Pad();
    ~Pad();
    static Pad* m_Instance;
};

#endif