#ifndef MENU_H
#define MENU_H
class Menu{
  Ogre::OverlayManager* overlayManager;

  bool menu_visible;

public:
  CEGUI::Window *menuWindow;
  Ogre::OverlayElement* overlayElement;

  Menu(){
    CEGUI::OgreRenderer& ogreRenderer =  CEGUI::OgreRenderer::bootstrapSystem();
    menu_visible = false;
    load_resources();

    init_gui();

    create_fps_overlay();
  }

  void switch_menu() {
    menu_visible = !menu_visible;
    menuWindow->setVisible(menu_visible);
  }

  void set_event_callback(CEGUI::Event::Subscriber callback){
    menuWindow->getChild("Exit")->subscribeEvent(
                                                 CEGUI::PushButton::EventClicked,
                                                 callback);
  }

private:
  void load_resources() {
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  }

  void init_gui() {
    CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
    CEGUI::GUIContext& guiContext =   CEGUI::System::getSingleton().getDefaultGUIContext();
    guiContext.setDefaultFont("DejaVuSans-12");
    // guiContext.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    guiContext.getMouseCursor().setPosition(CEGUI::Vector2f(0, 0));

    menuWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("TaharezLook.layout");
    guiContext.setRootWindow(menuWindow);
    menuWindow->hide();
  }

  void create_fps_overlay(){
    overlayManager = Ogre::OverlayManager::getSingletonPtr();
    overlayElement = overlayManager->getOverlayElement("fpsInfo");
    Ogre::Overlay *overlay = overlayManager->getByName("Info");
    overlay->show();
  }
};

#endif
