#include "main.h"
#include "pros/vision.h"
//Vision
Vision vis (5, pros::E_VISION_ZERO_CENTER);

Controller controller;
//Buttons
ControllerButton UP (ControllerDigital::up);
ControllerButton DOWN (ControllerDigital::down);
ControllerButton RIGHT (ControllerDigital::right);
ControllerButton LEFT (ControllerDigital::left);
ControllerButton X (ControllerDigital::X);
ControllerButton Y (ControllerDigital::Y);
ControllerButton A (ControllerDigital::A);
ControllerButton B (ControllerDigital::B);
ControllerButton R1 (ControllerDigital::R1);
ControllerButton R2 (ControllerDigital::R2);
ControllerButton L1 (ControllerDigital::L1);
ControllerButton L2 (ControllerDigital::L2);
//Channels
ControllerAnalog LeftY (ControllerAnalog::leftY);
ControllerAnalog LeftX (ControllerAnalog::leftX);
ControllerAnalog RightY (ControllerAnalog::rightY);
ControllerAnalog RightX(ControllerAnalog::rightX);
ADIEncoder sensor (1, 2, false);

ADIEncoder leftOdom (3,4, true);
ADIEncoder rightOdom (5,6,false);





//Motors
//Drive Motors
Motor right_front_drive (7, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::rotations);
Motor right_back_drive (10, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::rotations);
Motor left_front_drive (8, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::rotations);
Motor left_back_drive (11, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::rotations);
//Flywheel
Motor flywheel (15, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);
//Cap Scorer
Motor cap_Scorer (1, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
//Indexer
Motor indexer (4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
//Rollers
Motor rollers (3, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);




/* ****************************************************************AUTON SELECTOR*************************************************************/

const char *auton = "None";
// Stores the button clicked
lv_res_t btnm_action(lv_obj_t *btnm, const char *txt) {
  auton = txt;
  return LV_RES_OK;
}

// Draws a filled squared
lv_obj_t *drawRectangle(int x, int y, int width, int height, lv_color_t color) {
  lv_obj_t *obj1 = lv_obj_create(lv_scr_act(), NULL);

  lv_style_t *style1 = (lv_style_t *)malloc(sizeof(lv_style_t));
  lv_style_copy(style1, &lv_style_plain_color);
  style1->body.empty = 1;
  style1->body.border.color = color;
  style1->body.border.width = 300;
  style1->body.border.part = LV_BORDER_FULL;

  lv_obj_set_style(obj1, style1);
  lv_obj_set_pos(obj1, x, y);
  lv_obj_set_size(obj1, width, height);

  return obj1;
}

// Sets the Screen to a Color and Text
void screenM(lv_color_t color, char const *str) {
  lv_obj_t *obj = drawRectangle(0, 0, 480, 240, color);
  lv_obj_t *usercontrol = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(usercontrol, str);
  lv_obj_align(usercontrol, NULL, LV_ALIGN_CENTER, 0, 0);
}

// Logging

std::string s[3] = {"", "", ""};
void log(const char *str) {
  if (s[2] == str)
    return;
  else if (s[0] == "")
    s[0] = str;
  else if (s[1] == "" && s[0] != str)
    s[1] = str;
  else if (s[2] == "" && s[1] != str && s[1] != "")
    s[2] = str;
  else {
    s[0] = s[1];
    s[1] = s[2];
    s[2] = str;
  }
}
void logThread(void *param) {
  std::string o[3] = {"", "", ""};
  while (true) {
    if (o[0] != s[0]) {
      std::copy(std::begin(s), std::end(s), std::begin(o));
      for (int x = 0; x < 3; x++) {
        controller.setText(x, 0, "              ");
        pros::delay(50);
        controller.setText(x, 0, s[x].c_str());
        pros::delay(50);
      }
    } else
      pros::delay(10);
  }
}

// Creates an auton selector grid
void autonSelect() {
  auton = "None";
  static const char *auton_map[] = {
		"Insert",  "Insert", "Insert", "Insert",   "\n",    "Insert", "Insert", "Insert",  "Insert",
		 "\n",  "Insert", "Insert", "Insert",   "Insert",  "\n", "Insert", "Insert", "Insert", "Insert", ""};

  static lv_style_t style_bg;
  lv_style_copy(&style_bg, &lv_style_plain);
  style_bg.body.main_color = LV_COLOR_SILVER;
  style_bg.body.grad_color = LV_COLOR_SILVER;
  style_bg.body.padding.hor = 0;
  style_bg.body.padding.ver = 0;
  style_bg.body.padding.inner = 0;

  static lv_style_t style_btn_black;
	// Gradient on boxes
  lv_style_copy(&style_btn_black, &lv_style_btn_rel);
  style_btn_black.body.main_color = LV_COLOR_RED;
  style_btn_black.body.grad_color = LV_COLOR_BLUE;
  style_btn_black.body.border.color = LV_COLOR_MAKE(46, 51, 54);
  style_btn_black.body.border.width = 2;
  style_btn_black.body.radius = 0;

  static lv_style_t style_btn_pr;
  lv_style_copy(&style_btn_pr, &style_btn_black);
  style_btn_pr.body.main_color = LV_COLOR_CYAN;
  style_btn_pr.body.grad_color = LV_COLOR_CYAN;
	style_btn_pr.body.border.color = LV_COLOR_GREEN;
  style_btn_pr.text.color = LV_COLOR_MAKE(99, 99, 99);

  lv_obj_t *btnm1 = lv_btnm_create(lv_scr_act(), NULL);
  lv_btnm_set_toggle(btnm1, true, 0);
  lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BG, &style_bg);
  lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_REL, &style_btn_black);
  lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_PR, &style_btn_pr);
  lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_TGL_PR, &style_btn_pr);
  lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_TGL_REL, &style_btn_pr);
  lv_btnm_set_map(btnm1, auton_map);
  lv_btnm_set_action(btnm1, btnm_action);
  lv_obj_set_size(btnm1, 480, 240);
}
/* ****************************************************************AUTON SELECTOR*************************************************************/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
  leftOdom.reset();
  rightOdom.reset();


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	autonSelect();
}
