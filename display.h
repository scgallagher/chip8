#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
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

  Gtk::Box mainBox;

  Gtk::Box controlBox;
  Gtk::Frame controlFrame;
  Gtk::Button stepButton;

  Gtk::Box infoBox;
  Gtk::Frame infoFrame;
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
  Gtk::Frame stackFrame;
  Gtk::Box stackBoxInner;

  std::vector<Gtk::Box*> stackBoxes;
  std::vector<Gtk::Label*> stackLabels;

  Gtk::Box vBox;
  Gtk::Frame vFrame;
  Gtk::Box vBoxInner;

  std::vector<Gtk::Box*> vBoxes;
  std::vector<Gtk::Label*> vLabels;
};

#endif
