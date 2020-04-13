/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H
#include <print.h>


#define _QWERTY 0
#define _MAC 1
#define _LOWER 2
#define _RAISE 3



#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

static bool rbrc_down = false;
static bool plus_down = false;
static bool onMacLayer = false;
static bool raise_down = false;
static bool lower_down = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     RAISE, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                           KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
     KC_MUTE,                 KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                      KC_LCTL,KC_ENT,                        KC_SPC, LOWER,
                                      KC_TAB,_______,                         _______,  KC_DEL,
                                      KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT,
                                                                                    KC_MS_U, KC_MS_L, KC_BTN1, KC_MS_D, KC_MS_R

  ),

  [_MAC] = LAYOUT_5x6(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     RAISE, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                           KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
     KC_MUTE,                 KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                      KC_LGUI,KC_ENT,                        KC_SPC, LOWER,
                                      KC_TAB,_______,                         _______,  KC_DEL,
                                      KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT,
                                                                                    KC_MS_U, KC_MS_L, KC_BTN1, KC_MS_D, KC_MS_R
  ),
  [_LOWER] = LAYOUT_5x6(

     _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                        _______, _______ , KC_UP , _______ ,_______,_______,
     _______,_______,_______,_______,_______,_______,                        _______, KC_LEFT , KC_DOWN , KC_RIGHT ,_______,_______,
     _______,_______,_______,_______,_______,_______,                        _______, KC_MPRV , KC_MPLY , KC_MNXT ,_______ ,_______,
    KC_MUTE,                                  KC_NO,KC_PSCR,            _______, _______,
                                             KC_NO,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                                                                         KC_UP, KC_LEFT, KC_ENT, KC_DOWN, KC_RIGHT

  ),

  [_RAISE] = LAYOUT_5x6(
       KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______ ,LSFT(KC_LBRC),LSFT(KC_RBRC),
       _______,_______,_______  ,_______,_______,_______,                        _______,_______,_______,_______, KC_LBRC,KC_RBRC,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
       KC_MUTE,                                _______,_______,            KC_EQL ,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                                                                         KC_UP, KC_LEFT, KC_ENT, KC_DOWN, KC_RIGHT
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case LOWER:
        if (record->event.pressed)
        {
            lower_down = true;
            layer_on(_LOWER);
        }
        else
        {
            lower_down = false;
            layer_off(_LOWER);

        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed)
        {
            raise_down = true;
            layer_on(_RAISE);
        }
        else
        {
            raise_down = false;
            layer_off(_RAISE);

        }
        return false;
        break;
    case KC_RBRC:
        if (record->event.pressed)
        {
            if (plus_down)
            {
                if (onMacLayer) {
                    layer_on(_QWERTY);
                    layer_off(_MAC);

                    onMacLayer = false;
                }
                else
                {
                    layer_on(_MAC);
                    layer_off(_QWERTY);

                    onMacLayer = true;
                }
            }
            else
            {
                register_code16(KC_RBRC);
            }
            rbrc_down = true;
        }
        else
        {
            unregister_code16(KC_RBRC);
            rbrc_down = false;
        }
        return false;
        break;
    case KC_PLUS:
        if (record->event.pressed)
        {
            if (rbrc_down)
            {
                if (onMacLayer) {
                    layer_on(_QWERTY);
                    layer_off(_MAC);
                    onMacLayer = false;
                }
                else
                {
                    layer_on(_MAC);
                    layer_off(_QWERTY);
                    onMacLayer = true;
                }
            }
            else
            {
                register_code16(KC_PLUS);
            }
            plus_down = true;
        }
        else
        {
            unregister_code16(KC_PLUS);
            plus_down = false;
        }
        return false;
        break;
    }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if(raise_down){
            tap_code(KC_PGUP);
        }else if (lower_down) {
            tap_code16(LCTL(LSFT(KC_TAB)));
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if(raise_down){
            tap_code(KC_PGDN);
        }else if (lower_down) {
            tap_code16(LCTL(KC_TAB));
        }else{
            tap_code(KC_VOLU);
        }
    }
}
