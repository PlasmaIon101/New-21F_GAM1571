#pragma once

namespace fw
{

	class Event;
	class GameCore;

	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void AddEvent(Event* pEvent);
		void ProcessEvents(GameCore& pGameCore);

		std::queue<Event*> m_EventQueue;
	protected:
		
	};
}