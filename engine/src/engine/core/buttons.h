#pragma once

#include <stdint.h>

namespace prime {

	using Button = uint8_t;

	enum Buttons
	{
		button0 = 0,
		button1 = 1,
		button2 = 2,
		button3 = 3,
		button4 = 4,
		button5 = 5,
		button6 = 6,
		button7 = 7,

		buttonLast = button7,
		buttonLeft = button0,
		buttonRight = button1,
		buttonMiddle = button2
	};
}
