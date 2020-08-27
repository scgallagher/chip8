#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

class Display : public Gtk::Window
{

public:
  Display();
  virtual ~Display();

  void initializeStackLabels();
  void initializeVLabels();

  void setProgramCounterLabel(std::string);
  void setIndexLabel(std::string);
  void setStackPointerLabel(std::string);
  void setDelayTimerLabel(std::string);
  void setSoundTimerLabel(std::string);

  void setStackLabels(unsigned short*);
  void setVLabels(unsigned char*);

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Box mainBox, infoBox, controlBox;

  Gtk::Frame infoFrame, controlFrame, stackFrame, vFrame;

  Gtk::Button m_button;

  Gtk::Box infoBoxInner;
  Gtk::Box programCounterBox;
  Gtk::Label programCounterLabel;
  Gtk::Box indexBox;
  Gtk::Label indexLabel;
  Gtk::Box delayTimerBox;
  Gtk::Label delayTimerLabel;
  Gtk::Box soundTimerBox;
  Gtk::Label soundTimerLabel;
  Gtk::Box stackPointerBox;
  Gtk::Label stackPointerLabel;

  Gtk::Box stackBox;
  Gtk::Box stackBoxInner;
  Gtk::Box stack0Box;
  Gtk::Box stack1Box;
  Gtk::Box stack2Box;
  Gtk::Box stack3Box;
  Gtk::Box stack4Box;
  Gtk::Box stack5Box;
  Gtk::Box stack6Box;
  Gtk::Box stack7Box;
  Gtk::Box stack8Box;
  Gtk::Box stack9Box;
  Gtk::Box stack10Box;
  Gtk::Box stack11Box;
  Gtk::Box stack12Box;
  Gtk::Box stack13Box;
  Gtk::Box stack14Box;
  Gtk::Box stack15Box;
  Gtk::Label stack0Label;
  Gtk::Label stack1Label;
  Gtk::Label stack2Label;
  Gtk::Label stack3Label;
  Gtk::Label stack4Label;
  Gtk::Label stack5Label;
  Gtk::Label stack6Label;
  Gtk::Label stack7Label;
  Gtk::Label stack8Label;
  Gtk::Label stack9Label;
  Gtk::Label stack10Label;
  Gtk::Label stack11Label;
  Gtk::Label stack12Label;
  Gtk::Label stack13Label;
  Gtk::Label stack14Label;
  Gtk::Label stack15Label;

  Gtk::Box vBox;
  Gtk::Box vBoxInner;
  Gtk::Box v0Box;
  Gtk::Box v1Box;
  Gtk::Box v2Box;
  Gtk::Box v3Box;
  Gtk::Box v4Box;
  Gtk::Box v5Box;
  Gtk::Box v6Box;
  Gtk::Box v7Box;
  Gtk::Box v8Box;
  Gtk::Box v9Box;
  Gtk::Box v10Box;
  Gtk::Box v11Box;
  Gtk::Box v12Box;
  Gtk::Box v13Box;
  Gtk::Box v14Box;
  Gtk::Box v15Box;
  Gtk::Label v0Label;
  Gtk::Label v1Label;
  Gtk::Label v2Label;
  Gtk::Label v3Label;
  Gtk::Label v4Label;
  Gtk::Label v5Label;
  Gtk::Label v6Label;
  Gtk::Label v7Label;
  Gtk::Label v8Label;
  Gtk::Label v9Label;
  Gtk::Label v10Label;
  Gtk::Label v11Label;
  Gtk::Label v12Label;
  Gtk::Label v13Label;
  Gtk::Label v14Label;
  Gtk::Label v15Label;
};

#endif
