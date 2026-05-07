module;

#include "Gtkmm.hpp"

#include <span>
#include <spanstream>
#include <string>
#include <memory>

export module Inventory:Application;

import :MainWindow;
import :SplashScreen;

namespace Inventory
{
    [[nodiscard]] std::unique_ptr<char*[]> GetArgv(const std::span<std::string> values) noexcept
    {
        const auto size   = values.size();
        auto       result = std::make_unique<char*[]>(size);

        for ( size_t i = 0; i < size; ++i )
        {
            result[i] = const_cast<char*>(values[i].c_str());
        }

        return result;
    }

    class ApplicationController
    {
      public:
        explicit ApplicationController(const Glib::RefPtr<Gtk::Application>& application) noexcept
          : m_Application(application)
        {
        }

        void OnActivate() noexcept
        {
            ShowSplashScreen();
        }

      private:
        void ShowSplashScreen() noexcept
        {
            m_SplashScreen = std::make_unique<SplashScreen>();

            m_SplashOpacity = 1.0;
            m_SplashScreen->set_opacity(m_SplashOpacity);

            m_Application->add_window(*m_SplashScreen);
            m_SplashScreen->present();

            Glib::signal_timeout().connect(sigc::mem_fun(*this, &ApplicationController::StartSplashFadeOut), 1800);
        }

        bool StartSplashFadeOut() noexcept
        {
            Glib::signal_timeout().connect(sigc::mem_fun(*this, &ApplicationController::AnimateSplashFadeOut), 16);

            return false;
        }

        bool AnimateSplashFadeOut() noexcept
        {
            if ( m_SplashScreen == nullptr )
            {
                return false;
            }

            m_SplashOpacity -= 0.05;

            if ( m_SplashOpacity <= 0.0 )
            {
                m_SplashScreen->set_opacity(0.0);
                DestroySplashScreen();
                ShowMainWindow();

                return false;
            }

            m_SplashScreen->set_opacity(m_SplashOpacity);

            return true;
        }

        void DestroySplashScreen() noexcept
        {
            if ( m_SplashScreen == nullptr )
            {
                return;
            }

            m_SplashScreen->hide();
            m_Application->remove_window(*m_SplashScreen);
            m_SplashScreen.reset();
        }

        void ShowMainWindow() noexcept
        {
            m_MainWindow = std::make_unique<MainWindow>();

            m_Application->add_window(*m_MainWindow);
            m_MainWindow->present();
        }

      private:
        Glib::RefPtr<Gtk::Application> m_Application;
        std::unique_ptr<SplashScreen>  m_SplashScreen;
        std::unique_ptr<MainWindow>    m_MainWindow;
        double_t                       m_SplashOpacity { 1.0 };
    };

    export int32_t Main(const std::span<std::string> args) noexcept
    {
        g_setenv("GTK_CSD", "0", true);
        g_setenv("GDK_BACKEND", "win32", true);

        const auto            argv        = GetArgv(args);
        auto                  application = Gtk::Application::create("com.acrosstec.inventory");
        ApplicationController controller { application };

        application->signal_activate().connect(sigc::mem_fun(controller, &ApplicationController::OnActivate));

        return application->run(static_cast<int32_t>(args.size()), argv.get());
    }
}   // namespace Inventory

#include "Gtkmm-end.hpp"
