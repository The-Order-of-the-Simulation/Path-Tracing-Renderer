#include <common.hpp>

#include <fstream>
#include <sstream>

void write_render(image_buffer render_buffer)
{
	std::ofstream image_file;

	image_file.open("render.ppm");

	image_file << "P6\n" << render_buffer.size_x << " " << render_buffer.size_y << "\n255\n";

	for(unsigned int i = 0; i < render_buffer.size; i++)
	{
		// Quantization
		unsigned char channel_r = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].r), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_g = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].g), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_b = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].b), (unsigned int)0 ), (unsigned int)255);

		image_file << channel_r << channel_g << channel_b;
	}

	image_file.close();
}

void write_render_HDR(image_buffer render_buffer)
{
	std::ofstream image_file;

	image_file.open("render.pfm");

	image_file << "PF\n" << render_buffer.size_x << " " << render_buffer.size_y << "\n-1.0\n";

	for(unsigned int i = 0; i < render_buffer.size; i++)
	{
		// https://stackoverflow.com/questions/30923685/writing-floats-to-a-binary-file-in-c-equivalent-of-javas-dataoutputstream-w
		image_file.write( reinterpret_cast<const char*>(&render_buffer.buffer[i].r), sizeof(float) );
		image_file.write( reinterpret_cast<const char*>(&render_buffer.buffer[i].g), sizeof(float) );
		image_file.write( reinterpret_cast<const char*>(&render_buffer.buffer[i].b), sizeof(float) );
	}

	image_file.close();
}

void write_frame(image_buffer render_buffer, unsigned int frame_number)
{
	std::stringstream filename; filename.fill('0'); filename.width(3); filename << std::to_string(frame_number);

	std::string file_name = "render/frame" + filename.str() + ".ppm";

	std::ofstream image_file;

	image_file.open(file_name);

	image_file << "P6\n" << render_buffer.size_x << " " << render_buffer.size_y << "\n255\n";

	for(unsigned int i = 0; i < render_buffer.size; i++)
	{
		// Quantization
		unsigned char channel_r = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].r), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_g = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].g), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_b = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].b), (unsigned int)0 ), (unsigned int)255);

		image_file << channel_r << channel_g << channel_b;
	}

	image_file.close();
}