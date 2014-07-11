#include "Pad.h"
#include "GameLib/GameLib.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Input/Joystick.h"
using namespace GameLib::Input;

Pad* Pad::m_Instance = 0;

Pad::Pad()
{
}

Pad::~Pad()
{
}

void Pad::Create()
{
    ASSERT( !m_Instance );
    m_Instance = new Pad();
}

void Pad::Destroy()
{
    ASSERT( m_Instance );
    SAFE_DELETE( m_Instance );
}

Pad* Pad::Instance()
{
    return m_Instance;
}

bool Pad::isOn( Button b, int id ) const
{
    bool r = false;
    Manager m = Manager::instance();
    if( m.joystickNumber() > id ) {
        Joystick j = m.joystick(id);
        switch( b ) {
        case JUMP:  r = j.isOn(0) ? 1 : 0;    break;
        case UP:    r = j.isOn(Joystick::BUTTON_UP) ? 1 : 0;    break;            
        case DOWN:  r = j.isOn(Joystick::BUTTON_DOWN) ? 1 : 0;  break;
        case LEFT:  r = j.isOn(Joystick::BUTTON_LEFT) ? 1 : 0;  break;
        case RIGHT: r = j.isOn(Joystick::BUTTON_RIGHT) ? 1 : 0; break;
        default:    ASSERT(false);  break;
        }
    }
    Keyboard k = m.keyboard();
    if( id == 0 ) {
        char c = 0;
        switch (b) {
        case Pad::UP:       c = 'w';    break;
        case Pad::DOWN:     c = 's';    break;            
        case Pad::LEFT:     c = 'a';    break;
        case Pad::RIGHT:    c = 'd';    break;
        case Pad::JUMP:     c = 'f';    break;
        case Pad::FIRE1:    c = 'g';    break;
        default:    ASSERT(false);      break;
        }
        r = r || k.isOn(c);
    } 
    else if( id == 1 ) {
        char c = 0;
        switch (b) {
        case Pad::UP:       c = 'i';    break;
        case Pad::DOWN:     c = 'k';    break;            
        case Pad::LEFT:     c = 'j';    break;
        case Pad::RIGHT:    c = 'l';    break;
        case Pad::JUMP:     c = 'b';    break;
        case Pad::FIRE1:    c = 'n';    break;
        default:    ASSERT(false);      break;
        }
        r = r || k.isOn(c);
    }
    return r;
}

bool Pad::isTriggered( Button b, int id ) const
{
    bool r = false;
    Manager m = Manager::instance();
    if( m.joystickNumber() > id ) {
        Joystick j = m.joystick(id);
        switch( b ) {
        case JUMP:  r = j.isTriggered(0) ? 1 : 0;    break;
        case UP:    r = j.isTriggered(Joystick::BUTTON_UP) ? 1 : 0;    break;            
        case DOWN:  r = j.isTriggered(Joystick::BUTTON_DOWN) ? 1 : 0;  break;
        case LEFT:  r = j.isTriggered(Joystick::BUTTON_LEFT) ? 1 : 0;  break;
        case RIGHT: r = j.isTriggered(Joystick::BUTTON_RIGHT) ? 1 : 0; break;
        default:    ASSERT(false);  break;
        }
    }
    Keyboard k = m.keyboard();
    if( id == 0 ) {
        char c = 0;
        switch (b) {
        case Pad::UP:       c = 'w';    break;
        case Pad::DOWN:     c = 's';    break;            
        case Pad::LEFT:     c = 'a';    break;
        case Pad::RIGHT:    c = 'd';    break;
        case Pad::JUMP:     c = 'f';    break;
        case Pad::FIRE1:    c = 'g';    break;
        default:    ASSERT(false);      break;
        }
        r = r || k.isOn(c);
    } 
    else if( id == 1 ) {
        char c = 0;
        switch (b) {
        case Pad::UP:       c = 'i';    break;
        case Pad::DOWN:     c = 'k';    break;            
        case Pad::LEFT:     c = 'j';    break;
        case Pad::RIGHT:    c = 'l';    break;
        case Pad::JUMP:     c = 'b';    break;
        case Pad::FIRE1:    c = 'n';    break;
        default:    ASSERT(false);      break;
        }
        r = r || k.isTriggered(c);
    }
    return r;
}


