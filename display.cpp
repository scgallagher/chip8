#include "display.h"
#include <iostream>

void Display::initializeStackLabels() {
    stack0Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack0Box.add(stack0Label);
    stack0Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack0Box.set_spacing(5);
    stack0Box.set_margin_start(5);
    stack0Box.set_margin_end(5);
    stackBoxInner.add(stack0Box);

    stack1Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack1Box.add(stack1Label);
    stack1Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack1Box.set_spacing(5);
    stack1Box.set_margin_start(5);
    stack1Box.set_margin_end(5);
    stackBoxInner.add(stack1Box); 

    stack2Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack2Box.add(stack2Label);
    stack2Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack2Box.set_spacing(5);
    stack2Box.set_margin_start(5);
    stack2Box.set_margin_end(5);
    stackBoxInner.add(stack2Box); 

    stack3Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack3Box.add(stack3Label);
    stack3Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack3Box.set_spacing(5);
    stack3Box.set_margin_start(5);
    stack3Box.set_margin_end(5);
    stackBoxInner.add(stack3Box); 

    stack4Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack4Box.add(stack4Label);
    stack4Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack4Box.set_spacing(5);
    stack4Box.set_margin_start(5);
    stack4Box.set_margin_end(5);
    stackBoxInner.add(stack4Box); 

    stack5Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack5Box.add(stack5Label);
    stack5Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack5Box.set_spacing(5);
    stack5Box.set_margin_start(5);
    stack5Box.set_margin_end(5);
    stackBoxInner.add(stack5Box); 

    stack6Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack6Box.add(stack6Label);
    stack6Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack6Box.set_spacing(5);
    stack6Box.set_margin_start(5);
    stack6Box.set_margin_end(5);
    stackBoxInner.add(stack6Box); 

    stack7Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack7Box.add(stack7Label);
    stack7Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack7Box.set_spacing(5);
    stack7Box.set_margin_start(5);
    stack7Box.set_margin_end(5);
    stackBoxInner.add(stack7Box); 

    stack8Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack8Box.add(stack8Label);
    stack8Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack8Box.set_spacing(5);
    stack8Box.set_margin_start(5);
    stack8Box.set_margin_end(5);
    stackBoxInner.add(stack8Box); 

    stack9Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack9Box.add(stack9Label);
    stack9Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack9Box.set_spacing(5);
    stack9Box.set_margin_start(5);
    stack9Box.set_margin_end(5);
    stackBoxInner.add(stack9Box); 

    stack10Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack10Box.add(stack10Label);
    stack10Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack10Box.set_spacing(5);
    stack10Box.set_margin_start(5);
    stack10Box.set_margin_end(5);
    stackBoxInner.add(stack10Box); 

    stack11Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack11Box.add(stack11Label);
    stack11Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack11Box.set_spacing(5);
    stack11Box.set_margin_start(5);
    stack11Box.set_margin_end(5);
    stackBoxInner.add(stack11Box); 

    stack12Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack12Box.add(stack12Label);
    stack12Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack12Box.set_spacing(5);
    stack12Box.set_margin_start(5);
    stack12Box.set_margin_end(5);
    stackBoxInner.add(stack12Box); 

    stack13Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack13Box.add(stack13Label);
    stack13Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack13Box.set_spacing(5);
    stack13Box.set_margin_start(5);
    stack13Box.set_margin_end(5);
    stackBoxInner.add(stack13Box); 

    stack14Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack14Box.add(stack14Label);
    stack14Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack14Box.set_spacing(5);
    stack14Box.set_margin_start(5);
    stack14Box.set_margin_end(5);
    stackBoxInner.add(stack14Box); 

    stack15Label.set_justify(Gtk::JUSTIFY_LEFT);
    stack15Box.add(stack15Label);
    stack15Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    stack15Box.set_spacing(5);
    stack15Box.set_margin_start(5);
    stack15Box.set_margin_end(5);
    stackBoxInner.add(stack15Box);  
}

void Display::initializeVLabels() {
    v0Label.set_justify(Gtk::JUSTIFY_LEFT);
    v0Box.add(v0Label);
    v0Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v0Box.set_spacing(5);
    v0Box.set_margin_start(5);
    v0Box.set_margin_end(5);
    vBoxInner.add(v0Box);

    v1Label.set_justify(Gtk::JUSTIFY_LEFT);
    v1Box.add(v1Label);
    v1Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v1Box.set_spacing(5);
    v1Box.set_margin_start(5);
    v1Box.set_margin_end(5);
    vBoxInner.add(v1Box); 

    v2Label.set_justify(Gtk::JUSTIFY_LEFT);
    v2Box.add(v2Label);
    v2Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v2Box.set_spacing(5);
    v2Box.set_margin_start(5);
    v2Box.set_margin_end(5);
    vBoxInner.add(v2Box); 

    v3Label.set_justify(Gtk::JUSTIFY_LEFT);
    v3Box.add(v3Label);
    v3Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v3Box.set_spacing(5);
    v3Box.set_margin_start(5);
    v3Box.set_margin_end(5);
    vBoxInner.add(v3Box); 

    v4Label.set_justify(Gtk::JUSTIFY_LEFT);
    v4Box.add(v4Label);
    v4Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v4Box.set_spacing(5);
    v4Box.set_margin_start(5);
    v4Box.set_margin_end(5);
    vBoxInner.add(v4Box); 

    v5Label.set_justify(Gtk::JUSTIFY_LEFT);
    v5Box.add(v5Label);
    v5Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v5Box.set_spacing(5);
    v5Box.set_margin_start(5);
    v5Box.set_margin_end(5);
    vBoxInner.add(v5Box); 

    v6Label.set_justify(Gtk::JUSTIFY_LEFT);
    v6Box.add(v6Label);
    v6Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v6Box.set_spacing(5);
    v6Box.set_margin_start(5);
    v6Box.set_margin_end(5);
    vBoxInner.add(v6Box); 

    v7Label.set_justify(Gtk::JUSTIFY_LEFT);
    v7Box.add(v7Label);
    v7Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v7Box.set_spacing(5);
    v7Box.set_margin_start(5);
    v7Box.set_margin_end(5);
    vBoxInner.add(v7Box); 

    v8Label.set_justify(Gtk::JUSTIFY_LEFT);
    v8Box.add(v8Label);
    v8Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v8Box.set_spacing(5);
    v8Box.set_margin_start(5);
    v8Box.set_margin_end(5);
    vBoxInner.add(v8Box); 

    v9Label.set_justify(Gtk::JUSTIFY_LEFT);
    v9Box.add(v9Label);
    v9Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v9Box.set_spacing(5);
    v9Box.set_margin_start(5);
    v9Box.set_margin_end(5);
    vBoxInner.add(v9Box); 

    v10Label.set_justify(Gtk::JUSTIFY_LEFT);
    v10Box.add(v10Label);
    v10Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v10Box.set_spacing(5);
    v10Box.set_margin_start(5);
    v10Box.set_margin_end(5);
    vBoxInner.add(v10Box); 

    v11Label.set_justify(Gtk::JUSTIFY_LEFT);
    v11Box.add(v11Label);
    v11Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v11Box.set_spacing(5);
    v11Box.set_margin_start(5);
    v11Box.set_margin_end(5);
    vBoxInner.add(v11Box); 

    v12Label.set_justify(Gtk::JUSTIFY_LEFT);
    v12Box.add(v12Label);
    v12Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v12Box.set_spacing(5);
    v12Box.set_margin_start(5);
    v12Box.set_margin_end(5);
    vBoxInner.add(v12Box); 

    v13Label.set_justify(Gtk::JUSTIFY_LEFT);
    v13Box.add(v13Label);
    v13Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v13Box.set_spacing(5);
    v13Box.set_margin_start(5);
    v13Box.set_margin_end(5);
    vBoxInner.add(v13Box); 

    v14Label.set_justify(Gtk::JUSTIFY_LEFT);
    v14Box.add(v14Label);
    v14Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v14Box.set_spacing(5);
    v14Box.set_margin_start(5);
    v14Box.set_margin_end(5);
    vBoxInner.add(v14Box); 

    v15Label.set_justify(Gtk::JUSTIFY_LEFT);
    v15Box.add(v15Label);
    v15Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    v15Box.set_spacing(5);
    v15Box.set_margin_start(5);
    v15Box.set_margin_end(5);
    vBoxInner.add(v15Box);  
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

	m_button.set_label("Step");
  controlFrame.add(m_button);
  controlFrame.set_label("Controls");
  //add(m_button);

  controlBox.pack_start(controlFrame, Gtk::PACK_SHRINK);

  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &Display::on_button_clicked));

  show_all_children();
  //m_button.show();
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
