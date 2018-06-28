//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Menu
//

#pragma once

#include <irrlicht.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include "ManageStrings.hpp"
#include "Options.hpp"

namespace Indie {

	enum IdGui {
		GUI_ID_QUIT_BUTTON = 101,
		GUI_ID_PLAY_BUTTON,
		GUI_ID_OPTIONS_BUTTON,
		GUI_ID_SERVER_BUTTON,
		GUI_ID_MAP_BUTTON,
		GUI_ID_PLAY_MENU_ELEMENT,
		GUI_ID_OPTION_MENU_ELEMENT,
		GUI_ID_MAP_EDIT_MENU_ELEMENT,
		GUI_ID_MAIN_MENU_ELEMENT,
		GUI_ID_ROOMS_MENU_ELEMENT,
		GUI_ID_ROOMC_MENU_ELEMENT,
		GUI_ID_DOWN_ELEMENT,
		GUI_ID_JOIN_MENU_ELEMENT,
		GUI_ID_GAME_OPTIONS_ELEMENT,
		GUI_ID_READY_ELEMENT,
		GUI_ID_ROOM_BACK_BUTTON,
		GUI_ID_OPTION_BACK_BUTTON,
		GUI_ID_PLAY_BACK_BUTTON,
		GUI_ID_MAP_BACK_BUTTON,
		GUI_ID_FULLSCREEN,
		GUI_ID_PLAY_SERVER,
		GUI_ID_PLAY_CLIENT,
		GUI_ID_READY,
		GUI_ID_UNREADY,
		GUI_ID_MAP_EDITOR_BUTTON,
		GUI_ID_TCHAT_BUTTON,
		GUI_ID_MAP_RANDOM_BUTTON,
		GUI_ID_MAP_NAME,
		GUI_ID_MAP_SAVE_BUTTON,
		GUI_ID_DOWN_BUTTON,
		GUI_ID_LEAVE_GAME_BUTTON,
		GUI_ID_QUIT_GAME_BUTTON,
		GUI_ID_STAY_GAME_BUTTON,
		GUI_ID_JOIN_BUTTON,
		GUI_ID_JOIN_BACK_BUTTON,
		GUI_ID_LIST_MAP,
		GUI_ID_IP,
		GUI_ID_NUMPAD_0,
		GUI_ID_NUMPAD_1,
		GUI_ID_NUMPAD_2,
		GUI_ID_NUMPAD_3,
		GUI_ID_NUMPAD_4,
		GUI_ID_NUMPAD_5,
		GUI_ID_NUMPAD_6,
		GUI_ID_NUMPAD_7,
		GUI_ID_NUMPAD_8,
		GUI_ID_NUMPAD_9,
		GUI_ID_NUMPAD_DOT,
		GUI_ID_NUMPAD_DEL,
		GUI_ID_SOUND,
		GUI_ID_LOCAL,
		GUI_ID_LOCAL_BACK,
		GUI_ID_LOCAL_MAPS,
		GUI_ID_PLAY_LOCAL,
		GUI_ID_NB_PLAYER,
		GUI_ID_NB_AI,
		GUI_ID_HOST_NAME,
		GUI_ID_SAVE_WINDOW,
		GUI_ID_LOAD_SAVE,
		GUI_ID_OPEN_SAVE_WINDOW,
		GUI_ID_LIST_SAVE,
		GUI_ID_CLIENT_NAME,
	};


	enum AppState {
		MENU,
		QUIT,
		OPTION,
		GEN_MAP,
		MAPPING,
		LAUNCH_SERVER,
		CONNECT,
		READY,
		UNREADY,
		PLAY,
		SERVER_DOWN,
		SPEC,
		LOCAL,
		NONE
	};

	struct SpriteMenu {
	public:
		SpriteMenu() {};
		~SpriteMenu() {};
		std::vector<irr::core::recti> m_images;
		irr::core::recti m_zone;
		AppState  m_return;
	};

	class Menu {
	public:
		Menu();
		~Menu();
		void loadMenu(irr::IrrlichtDevice *, const Options &);
		void initSpriteMenu(std::vector<SpriteMenu> &);

		void loadBackground();
		void loadMainMenu();
		void loadOptionsMenu();
		void loadMapMenu();
		void loadPlayMenu();
		void loadRoomSMenu();
		void loadRoomCMenu();
		void loadDownMenu();
		void loadGameOptionsMenu();
		void loadJoinMenu();
		void loadReadyMenu();
		void chooseMap(irr::s32);
		void loadSoundBtn();
		void loadLocalGame();
		void openSaveWindow();

		void errorMessage(const std::string &, irr::gui::IGUIElement *);

	public:
		irr::gui::IGUIElement *m_root;
		irr::gui::IGUIElement *m_main;
		irr::gui::IGUIElement *m_option;
		irr::gui::IGUIElement *m_play;
		irr::gui::IGUIElement *m_roomS;
		irr::gui::IGUIElement *m_roomC;
		irr::gui::IGUIElement *m_down;
		irr::gui::IGUIElement *m_mapMenu;
		irr::gui::IGUIElement *m_mapEdit;
		irr::gui::IGUIElement *m_gameOptions;
		irr::gui::IGUIElement *m_join;
		irr::gui::IGUIElement *m_ready;
		irr::gui::IGUIElement *m_local;

	private:
		irr::gui::IGUIFont *m_font;
		irr::scene::ISceneManager *m_sceneManager;
		irr::video::IVideoDriver *m_driver;
		irr::gui::IGUIEnvironment *m_gui;
		irr::video::ITexture* m_images;
		std::vector<irr::gui::IGUIButton *> m_btns;
		std::vector<irr::gui::IGUIButton *> m_small_btns;
		std::vector<irr::gui::IGUIButton *> m_square_btns;
		Options m_opt;

		std::size_t m_height;
		std::size_t m_width;
		std::vector<std::string> m_map;
		std::size_t m_small_height;
		std::size_t m_small_width;
		std::size_t m_square_height;
		std::size_t m_square_width;
		std::size_t m_xRight;
		std::size_t m_xLeft;
	};
}