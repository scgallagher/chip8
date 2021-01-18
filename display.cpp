#include "display.h"
#include <iostream>

void Display::initializeRegisterLabels(Gtk::Box *mainBox, Gtk::Box *outerBox, Gtk::Box *innerBox, Gtk::Frame *frame, void (Display::*initializeLabels)()) {
  outerBox->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  outerBox->set_spacing(5);
  mainBox->pack_start(*outerBox, Gtk::PACK_SHRINK);
  outerBox->pack_start(*frame, Gtk::PACK_SHRINK);
  frame->set_label("Stack");
  innerBox->set_orientation(Gtk::ORIENTATION_VERTICAL);
  innerBox->set_spacing(5);
  frame->add(*innerBox);

  (this->*initializeLabels)();
}

void Display::initializeStackLabels() {
    for (int i = 0; i < 16; i++) {
      Gtk::Label *label = new Gtk::Label();
      label->set_justify(Gtk::JUSTIFY_LEFT);
      stackLabels.push_back(label);
      
      Gtk::Box *box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
      box->set_margin_start(5);
      box->set_margin_end(5);
      box->add(*label);
      stackBoxes.push_back(box);

      stackBoxInner->add(*box);
    }  
}

void Display::initializeVLabels() {
    for (int i = 0; i < 16; i++) {
      Gtk::Label *label = new Gtk::Label();
      label->set_justify(Gtk::JUSTIFY_LEFT);
      vLabels.push_back(label);

      Gtk::Box *box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
      box->set_margin_start(5);
      box->set_margin_end(5);
      box->add(*label);
      vBoxes.push_back(box);

      vBoxInner->add(*box);
    }
}

void Display::initializeLabel(Gtk::Label *label, Gtk::Box *labelBox, Gtk::Box *wrappingBox) {
  label->set_justify(Gtk::JUSTIFY_LEFT); 

  labelBox->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  labelBox->set_spacing(5);
  labelBox->set_margin_start(5);
  labelBox->set_margin_end(5);
  labelBox->add(*label);

  wrappingBox->add(*labelBox);
}

void Display::instantiateLabels() {
  mainBox = new Gtk::Box();

  controlBox = new Gtk::Box();
  controlFrame = new Gtk::Frame();

  infoBox = new Gtk::Box();
  infoFrame = new Gtk::Frame();
  infoBoxInner = new Gtk::Box();

  programCounterBox = new Gtk::Box();
  programCounterLabel = new Gtk::Label();
  indexBox = new Gtk::Box();
  indexLabel = new Gtk::Label();
  delayTimerBox = new Gtk::Box();
  delayTimerLabel = new Gtk::Label();
  soundTimerBox = new Gtk::Box();
  soundTimerLabel = new Gtk::Label();
  stackPointerBox = new Gtk::Box();
  stackPointerLabel = new Gtk::Label();

  stackBox = new Gtk::Box();
  stackFrame = new Gtk::Frame();
  stackBoxInner = new Gtk::Box();

  vBox = new Gtk::Box();
  vFrame = new Gtk::Frame();
  vBoxInner = new Gtk::Box();;
}

Display::Display() {
  set_title("Chip8 Emulator");
  set_border_width(50);

  instantiateLabels();

  mainBox->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  mainBox->set_spacing(5);
  add(*mainBox);

  infoBox->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  infoBox->set_spacing(5);
  mainBox->pack_start(*infoBox, Gtk::PACK_SHRINK);

  infoFrame->set_label("Registers");
  infoBoxInner->set_orientation(Gtk::ORIENTATION_VERTICAL);
  infoBoxInner->set_spacing(5);
  infoFrame->add(*infoBoxInner);
  infoBox->pack_start(*infoFrame, Gtk::PACK_SHRINK);

  initializeLabel(programCounterLabel, programCounterBox, infoBoxInner);
  initializeLabel(indexLabel, indexBox, infoBoxInner);
  initializeLabel(delayTimerLabel, delayTimerBox, infoBoxInner); 
  initializeLabel(soundTimerLabel, soundTimerBox, infoBoxInner);
  initializeLabel(stackPointerLabel, stackPointerBox, infoBoxInner); 

  initializeRegisterLabels(mainBox, stackBox, stackBoxInner, stackFrame, &Display::initializeStackLabels);
  initializeRegisterLabels(mainBox, vBox, vBoxInner, vFrame, &Display::initializeVLabels);

  controlBox->set_orientation(Gtk::ORIENTATION_VERTICAL);
  controlBox->set_spacing(5);
  mainBox->pack_start(*controlBox, Gtk::PACK_SHRINK);

	stepButton.set_label("Step");
  controlFrame->add(stepButton);
  controlFrame->set_label("Controls");

  controlBox->pack_start(*controlFrame, Gtk::PACK_SHRINK);

  stepButton.signal_clicked().connect(sigc::mem_fun(*this,
              &Display::on_button_clicked));

  show_all_children();
}

void Display::setProgramCounterLabel(std::string value) {
  programCounterLabel->set_text("pc: " + value);
}

void Display::setIndexLabel(std::string value) {
  indexLabel->set_text("I: " + value);
}

void Display::setStackPointerLabel(std::string value) {
  stackPointerLabel->set_text("sp: " + value);
}

void Display::setDelayTimerLabel(std::string value) {
  delayTimerLabel->set_text("dt: " + value);
}

void Display::setSoundTimerLabel(std::string value) {
  soundTimerLabel->set_text("st: " + value);
}

Display::~Display()
{
}
