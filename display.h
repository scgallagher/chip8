#ifndef DISPLAY_H
#define DISPLAY_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Display : public Gtk::Window
{

public:
  Display();
  virtual ~Display();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
};

#endif
