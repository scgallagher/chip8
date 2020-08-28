#include "display.h"
#include <iostream>

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

      stackBoxInner.add(*box);
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

      vBoxInner.add(*box);
    }
}

Display::Display() {
  set_title("Chip8 Emulator");
  set_border_width(50);

  mainBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  mainBox.set_spacing(5);
  add(mainBox);

  infoBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  infoBox.set_spacing(5);
  mainBox.pack_start(infoBox, Gtk::PACK_SHRINK);

  infoFrame.set_label("Registers");
  infoBoxInner.set_orientation(Gtk::ORIENTATION_VERTICAL);
  infoBoxInner.set_spacing(5);
  infoFrame.add(infoBoxInner);
  infoBox.pack_start(infoFrame, Gtk::PACK_SHRINK);

  programCounterLabel.set_justify(Gtk::JUSTIFY_LEFT); 
  programCounterBox.add(programCounterLabel);
  programCounterBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  programCounterBox.set_spacing(5);
  programCounterBox.set_margin_start(5);
  programCounterBox.set_margin_end(5);
  infoBoxInner.add(programCounterBox);
  
  indexLabel.set_justify(Gtk::JUSTIFY_LEFT); 
  indexBox.add(indexLabel);
  indexBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  indexBox.set_spacing(5);
  indexBox.set_margin_start(5);
  indexBox.set_margin_end(5);
  infoBoxInner.add(indexBox);

  delayTimerLabel.set_justify(Gtk::JUSTIFY_LEFT);
  delayTimerBox.add(delayTimerLabel);
  delayTimerBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  delayTimerBox.set_spacing(5);
  delayTimerBox.set_margin_start(5);
  delayTimerBox.set_margin_end(5);
  infoBoxInner.add(delayTimerBox); 

  soundTimerLabel.set_justify(Gtk::JUSTIFY_LEFT);
  soundTimerBox.add(soundTimerLabel);
  soundTimerBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  soundTimerBox.set_spacing(5);
  soundTimerBox.set_margin_start(5);
  soundTimerBox.set_margin_end(5);
  infoBoxInner.add(soundTimerBox);

  stackPointerLabel.set_justify(Gtk::JUSTIFY_LEFT);
  stackPointerBox.add(stackPointerLabel);
  stackPointerBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  stackPointerBox.set_spacing(5);
  stackPointerBox.set_margin_start(5);
  stackPointerBox.set_margin_end(5);
  infoBoxInner.add(stackPointerBox); 

  stackBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  stackBox.set_spacing(5);
  mainBox.pack_start(stackBox, Gtk::PACK_SHRINK);
  stackBox.pack_start(stackFrame, Gtk::PACK_SHRINK);
  stackFrame.set_label("Stack");
  stackBoxInner.set_orientation(Gtk::ORIENTATION_VERTICAL);
  stackBoxInner.set_spacing(5);
  stackFrame.add(stackBoxInner);
  initializeStackLabels();

  vBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vBox.set_spacing(5);
  mainBox.pack_start(vBox, Gtk::PACK_SHRINK);
  vBox.pack_start(vFrame, Gtk::PACK_SHRINK);
  vFrame.set_label("V Registers");
  vBoxInner.set_orientation(Gtk::ORIENTATION_VERTICAL);
  vBoxInner.set_spacing(5);
  vFrame.add(vBoxInner);
  initializeVLabels();

  controlBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
  controlBox.set_spacing(5);
  mainBox.pack_start(controlBox, Gtk::PACK_SHRINK);

	stepButton.set_label("Step");
  controlFrame.add(stepButton);
  controlFrame.set_label("Controls");

  controlBox.pack_start(controlFrame, Gtk::PACK_SHRINK);

  stepButton.signal_clicked().connect(sigc::mem_fun(*this,
              &Display::on_button_clicked));

  show_all_children();
}

void Display::setProgramCounterLabel(std::string value) {
  programCounterLabel.set_text("pc: " + value);
}

void Display::setIndexLabel(std::string value) {
  indexLabel.set_text("I: " + value);
}

void Display::setStackPointerLabel(std::string value) {
  stackPointerLabel.set_text("sp: " + value);
}

void Display::setDelayTimerLabel(std::string value) {
  delayTimerLabel.set_text("dt: " + value);
}

void Display::setSoundTimerLabel(std::string value) {
  soundTimerLabel.set_text("st: " + value);
}

Display::~Display()
{
}
