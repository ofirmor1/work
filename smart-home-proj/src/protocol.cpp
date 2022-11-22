#include "protocol.hpp"

namespace home
{

std::string makeLine(home::Event a_event)
{
    std::string line(a_event.m_timeStamp + "|" + a_event.m_eventType + "|" + a_event.m_payload + "|" + a_event.m_floor + "|" + a_event.m_room);
	return line;
}

int PackLine(std::string a_line, void* a_buffer)
{
    char* pack = static_cast<char*> (a_buffer);
    char* copy = (char*) a_line.c_str();
    int size = strlen(copy);
	*pack = size;
	for(int i = 1; i < size + 1; ++i)
	{
		*(pack + i) = *(copy + i - 1);
	}
	a_buffer = pack;
    return size + 1;
}

std::string UnpackLine(void* a_buffer)
{
    char* pack = static_cast<char*> (a_buffer);
    int lineSize = *pack;
    char copy[1000]; 
	strncpy(copy, pack, lineSize + 1); 
	*(copy + lineSize + 1) = '\0';
	std::string line((copy + 1), lineSize);
    return  line;
}

home::Event makeEvent(std::string a_line)
{
	home::Event event;

    size_t begine = 0;
    size_t end = a_line.find('|', begine);
    event.m_timeStamp = a_line.substr(begine, end-begine);

    begine = end + 1;
    end = a_line.find('|', begine);
    event.m_eventType = a_line.substr(begine, end-begine);
    
    begine = end + 1;
    end = a_line.find('|', begine);
    event.m_payload = a_line.substr(begine, end-begine);

    begine = end + 1;
    end = a_line.find('|', begine);
    event.m_floor = a_line.substr(begine, end-begine);

    begine = end + 1;
    end = a_line.find('|', begine);
    event.m_room = a_line.substr(begine, end-begine);

	return event;
}


} //namespace home