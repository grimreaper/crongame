#include <kernel.h>

Kernel::Kernel() : double_buffer (NULL)
{
}

Kernel::Kernel(const Kernel&) : double_buffer (NULL) {}
//Kernel Kernel::operator=(const Kernel& newKernel) { return this; }


void Kernel::init()
{
	double_buffer = create_bitmap(SCREEN_W,SCREEN_H);
	if (!double_buffer)
	{
		raise_error("Kernel::init() - can't create double buffer!");
	}
	clear_bitmap(double_buffer);
}

void Kernel::shutdown()
{
	if (double_buffer)
	{
		destroy_bitmap(double_buffer);
	}
      double_buffer = NULL;
}

Kernel::~Kernel()
{
	shutdown(); // we shutdown on delete :)
}

