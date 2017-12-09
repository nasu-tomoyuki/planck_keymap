/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * docker run -e keyboard=planck -e subproject=rev4 -e keymap=my_keymap --rm -v $('pwd'):/qmk:rw jackhumbert/qmk_firmware make BACKLIGHT_ENABLE=yes
 * https://github.com/qmk/qmk_flasher/releases
 */

#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NAV,
  _ADJUST
};

enum planck_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  BACKLIT,
  C_ESC_TILDE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc~ |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Tab/Ctl|A/Ctl|   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ;/Ctl|   "  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |      |半/GUI| Lower|Sht/Sp| Enter| Raise|全/NAV|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {C_ESC_TILDE,		KC_Q,			KC_W,		KC_E,				KC_R,	KC_T,			KC_Y,		KC_U,		KC_I,				KC_O,		KC_P,				KC_BSPC},
  {LCTL_T(KC_TAB),	LCTL_T(KC_A),	KC_S,		KC_D,				KC_F,   KC_G,			KC_H,		KC_J,    	KC_K,				KC_L,		LCTL_T(KC_SCLN),	KC_QUOT},
  {KC_LSFT,			KC_Z,			KC_X,		KC_C,				KC_V,	KC_B,			KC_N,		KC_M,    	KC_COMM,			KC_DOT,		KC_SLSH,			KC_BSLS },
  {KC_LCTL,			KC_LALT,		_______,	LGUI_T(KC_LANG2),	LOWER,	LSFT_T(KC_SPC),	KC_ENT,		RAISE,		LT(_NAV, KC_LANG1),	_______,	_______,			BACKLIT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  | 1/Ctl|   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  | 0/Ctl|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  F12 |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD,	KC_EXLM,		KC_AT,		KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,	KC_ASTR,    KC_LPRN,	KC_RPRN,		_______},
  {KC_GRV,	LCTL_T(KC_1),	KC_2,		KC_3,    KC_4,    KC_5,    KC_6,	KC_7,		KC_8,		KC_9,		LCTL_T(KC_0),	_______},
  {_______,	KC_F1,			KC_F2,		KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,		KC_F8,		KC_F9,		KC_F10,			KC_F11},
  {_______,	_______,		_______,	_______, _______, _______, _______, _______,	_______,    _______,	_______,		KC_F12}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  `   |      |      |      |      |      |      |  {   |  }   |  _   |  +   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | HOME | PGUP |  [   |  ]   |  -   |  =   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | END  | PGDN |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV, _______, _______, _______, _______, _______,	_______, S(KC_LBRC),	S(KC_RBRC), S(KC_MINS), S(KC_EQL),	_______, },
  {_______, _______, _______, _______, _______, KC_HOME,	KC_PGUP, KC_LBRC,		KC_RBRC,    KC_MINS,    KC_EQL,		_______, },
  {_______, _______, _______, _______, _______, KC_END,		KC_PGDN, _______,		_______,    _______,    _______,	_______, },
  {_______, _______, _______, _______, _______, _______,	_______, _______,		_______,    _______,    _______,	_______, },
},

/* Navigation
 * ,-----------------------------------------+-----------------------------------------.
 * |      |      |      |      |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------+-----------------------------------------'
 */
[_NAV] = {
  {_______, _______, _______, _______, _______, _______,	_______, _______,		KC_UP,		_______,    _______,	_______, },
  {_______, _______, _______, _______, _______, _______, 	_______, KC_LEFT,		KC_DOWN,    KC_RIGHT,    _______,	_______, },
  {_______, _______, _______, _______, _______, _______, 	_______, _______,		_______,    _______,    _______,	_______, },
  {_______, _______, _______, _______, _______, _______, 	_______, _______,		_______,    _______,    _______,	_______, },
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, _______,  _______, _______, _______,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


// /* Qwerty
//  * ,-----------------------------------------------------------------------------------.
//  * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_QWERTY] = {
//   {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
//   {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
//   {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
//   {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
// },

// /* Lower
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_LOWER] = {
//   {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC},
//   {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE},
//   {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______},
//   {_______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY}
// },
// 
// /* Raise
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_RAISE] = {
//   {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
//   {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
//   {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
//   {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
// },
// 
// /* Adjust (Lower + Raise)
//  * ,-----------------------------------------------------------------------------------.
//  * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_ADJUST] = {
//   {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
//   {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______,  _______},
//   {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
//   {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
// }


};



#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif



// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case C_ESC_TILDE:
        if (record->event.pressed) {
            int oneshot_shift = get_oneshot_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
            int shift = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
            // SHIFT を押していたらチルダ ~
            if (shift || oneshot_shift) {
                clear_oneshot_mods();
                // !shift の場合、つまり oneshot mods の場合は自前でシフトを押して後で戻す
                if (!shift) {
                    register_code(KC_LSFT);
                }

                // SHIFT + ` = ~
                register_code(KC_GRV);
                unregister_code(KC_GRV);

                if (!shift) {
                    unregister_code(KC_LSFT);
                }
            } else { // SHIFT を押していなければ ESC
                register_code(KC_ESC);
                unregister_code(KC_ESC);
            }
        }
        return false;
  }
  return true;
}
