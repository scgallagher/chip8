#include "display.h"
#include <iostream>

Display::Display() {
  set_border_width(50);

	m_button.set_label("Step");

  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &Display::on_button_clicked));

  add(m_button);

  m_button.show();
}

Display::~Display()
{
}
