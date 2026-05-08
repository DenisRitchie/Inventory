module;

#include "Gtkmm.hpp"
#include "Resources/Gtk/SplashScreen_gresource.h"

#include <span>
#include <spanstream>
#include <string>
#include <memory>

export module Inventory:Application;

import :MainWindow;
import :SplashScreen;
import :LoginWindow;

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

    class Application final : public Gtk::Application
    {
      protected:
        Application()
          : Gtk::Application("com.acrosstec.inventory")
        {
        }

        void on_startup() override
        {
            Gtk::Application::on_startup();
            RegisterResources();
        }

        void on_activate() override
        {
            Gtk::Application::on_activate();
            ShowSplashScreen();
        }

      public:
        static Glib::RefPtr<Application> Create() noexcept
        {
            return Glib::make_refptr_for_instance<Application>(new Application());
        }

        virtual ~Application() noexcept override
        {
            UnregisterResources();
        }

      private:
        void RegisterResources() noexcept
        {
            if ( m_ResourcesRegistered )
            {
                return;
            }

            SplashScreen_gresource_register_resource();
            m_ResourcesRegistered = true;
        }

        void UnregisterResources() noexcept
        {
            if ( not m_ResourcesRegistered )
            {
                return;
            }

            SplashScreen_gresource_unregister_resource();
            m_ResourcesRegistered = false;
        }

        void ShowSplashScreen() noexcept
        {
            if ( m_SplashScreen != nullptr )
            {
                m_SplashScreen->present();
                return;
            }

            m_SplashScreen = std::make_unique<SplashScreen>();

            m_SplashOpacity = 1.0;
            m_SplashScreen->set_opacity(m_SplashOpacity);

            add_window(*m_SplashScreen);
            m_SplashScreen->present();

            Glib::signal_timeout().connect(sigc::mem_fun(*this, &Application::StartSplashFadeOut), 1000);
        }

        bool StartSplashFadeOut() noexcept
        {
            Glib::signal_timeout().connect(sigc::mem_fun(*this, &Application::AnimateSplashFadeOut), 16);
            return false;   // Stop this timeout, as the next one will handle the animation
        }

        bool AnimateSplashFadeOut() noexcept
        {
            if ( m_SplashScreen == nullptr )
            {
                // This should not happen, but if it does, stop the animation and show the login window
                return false;
            }

            m_SplashOpacity -= 0.05;

            if ( m_SplashOpacity <= 0.0 )
            {
                m_SplashScreen->set_opacity(0.0);
                ShowLoginWindow();

                return false;   // Stop this timeout, as the animation is complete and the login window is now shown
            }

            m_SplashScreen->set_opacity(m_SplashOpacity);
            return true;   // Continue on the next timeout, as the animation is not yet complete
        }

        void ShowLoginWindow() noexcept
        {
            DestroySplashScreen();

            if ( m_LoginWindow != nullptr )
            {
                m_LoginWindow->present();
                return;
            }

            m_LoginWindow = std::make_unique<LoginWindow>();
            m_LoginWindow->signal_login_success().connect(sigc::mem_fun(*this, &Application::OnLoginSuccess));

            add_window(*m_LoginWindow);
            m_LoginWindow->present();
        }

        void OnLoginSuccess() noexcept
        {
            DestroyLoginWindow();
            ShowMainWindow();
        }

        void ShowMainWindow() noexcept
        {
            if ( m_MainWindow != nullptr )
            {
                m_MainWindow->present();
                return;
            }

            m_MainWindow = std::make_unique<MainWindow>();

            add_window(*m_MainWindow);
            m_MainWindow->present();
        }

        void DestroySplashScreen() noexcept
        {
            if ( m_SplashScreen == nullptr )
            {
                return;
            }

            m_SplashScreen->hide();
            remove_window(*m_SplashScreen);
            m_SplashScreen.reset();
        }

        void DestroyLoginWindow() noexcept
        {
            if ( m_LoginWindow == nullptr )
            {
                return;
            }

            m_LoginWindow->hide();
            remove_window(*m_LoginWindow);
            m_LoginWindow.reset();
        }

      private:
        std::unique_ptr<SplashScreen> m_SplashScreen;
        std::unique_ptr<LoginWindow>  m_LoginWindow;
        std::unique_ptr<MainWindow>   m_MainWindow;

        double_t m_SplashOpacity { 1.0 };
        bool     m_ResourcesRegistered { false };
    };

    export int32_t Main(const std::span<std::string> args) noexcept
    {
        g_setenv("GTK_CSD", "0", true);
        g_setenv("GDK_BACKEND", "win32", true);

        const auto argv = GetArgv(args);

        auto application = Application::Create();
        return application->run(static_cast<int32_t>(args.size()), argv.get());
    }
}   // namespace Inventory

#include "Gtkmm-end.hpp"
