module;

#include "Gtkmm.hpp"

#include <functional>
#include <memory>

export module Inventory:LoginWindow;

import :BaseWindow;

export namespace Inventory
{
    class LoginWindow : public BaseWindow
    {
      public:
        explicit LoginWindow(std::function<void()> on_login_success) noexcept
          : m_Root(Gtk::Orientation::VERTICAL)
          , m_Card(Gtk::Orientation::VERTICAL)
          , m_ButtonBox(Gtk::Orientation::HORIZONTAL)
          , m_OnLoginSuccess(std::move(on_login_success))
        {
            InitializeComponents();
        }

        virtual void InitializeComponents() noexcept override
        {
            BaseWindow::InitializeComponents();

            set_title("AcrossTec Inventory - Login");
            set_default_size(460, 420);
            set_size_request(460, 420);
            set_resizable(false);

            LoadStyles();

            add_css_class("login-window");

            m_Root.set_margin_top(32);
            m_Root.set_margin_bottom(32);
            m_Root.set_margin_start(32);
            m_Root.set_margin_end(32);
            m_Root.set_valign(Gtk::Align::CENTER);
            m_Root.set_halign(Gtk::Align::CENTER);

            m_Card.add_css_class("login-card");
            m_Card.set_size_request(360, -1);
            m_Card.set_spacing(16);
            m_Card.set_margin_top(24);
            m_Card.set_margin_bottom(24);
            m_Card.set_margin_start(24);
            m_Card.set_margin_end(24);

            m_Title.set_text("AcrossTec Inventory");
            m_Title.add_css_class("login-title");
            m_Title.set_halign(Gtk::Align::CENTER);

            m_Subtitle.set_text("Inicia sesión para continuar");
            m_Subtitle.add_css_class("login-subtitle");
            m_Subtitle.set_halign(Gtk::Align::CENTER);

            m_UserEntry.set_placeholder_text("Usuario");
            m_UserEntry.set_hexpand(true);

            m_PasswordEntry.set_placeholder_text("Contraseña");
            m_PasswordEntry.set_visibility(false);
            m_PasswordEntry.set_hexpand(true);

            m_LoginButton.set_label("Entrar");
            m_LoginButton.add_css_class("suggested-action");
            m_LoginButton.set_hexpand(true);

            m_ButtonBox.set_halign(Gtk::Align::FILL);
            m_ButtonBox.append(m_LoginButton);

            m_Card.append(m_Title);
            m_Card.append(m_Subtitle);
            m_Card.append(m_UserEntry);
            m_Card.append(m_PasswordEntry);
            m_Card.append(m_ButtonBox);

            m_Root.append(m_Card);

            set_child(m_Root);

            m_LoginButton.signal_clicked().connect(sigc::mem_fun(*this, &LoginWindow::OnLoginButtonClicked));
            m_UserEntry.signal_activate().connect([this]() { m_PasswordEntry.grab_focus(); });
            m_PasswordEntry.signal_activate().connect(sigc::mem_fun(*this, &LoginWindow::OnLoginButtonClicked));
        }

      private:
        void OnLoginButtonClicked() noexcept
        {
            const auto user     = m_UserEntry.get_text();
            const auto password = m_PasswordEntry.get_text();

            if ( user == "admin" && password == "1234" )
            {
                if ( m_OnLoginSuccess )
                {
                    m_OnLoginSuccess();
                }

                return;
            }

            ShowInvalidCredentialsDialog();
        }

        void ShowInvalidCredentialsDialog() noexcept
        {
            if ( m_ErrorDialog != nullptr )
            {
                m_ErrorDialog->present();
                return;
            }

            m_ErrorDialog = std::make_unique<Gtk::MessageDialog>(*this, "Datos incorrectos", false, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK, true);

            m_ErrorDialog->set_title("Login incorrecto");
            m_ErrorDialog->set_secondary_text("El usuario o la contraseña no coinciden.");
            m_ErrorDialog->set_modal(true);
            m_ErrorDialog->set_transient_for(*this);

            m_ErrorDialog->signal_response().connect([this](int) {
                if ( m_ErrorDialog != nullptr )
                {
                    m_ErrorDialog->hide();
                    m_ErrorDialog.reset();
                }
            });

            m_ErrorDialog->present();
        }

        void LoadStyles() noexcept
        {
            m_CssProvider = Gtk::CssProvider::create();

            m_CssProvider->load_from_data(
                R"css(
                    window.login-window {
                        background: #07111f;
                    }

                    .login-card {
                        background: #0b1b2f;
                        border-radius: 18px;
                        box-shadow: 8px 4px 18px rgba(0, 18, 58, 0.55);
                    }

                    .login-title {
                        font-size: 24px;
                        font-weight: 700;
                        color: #ffffff;
                    }

                    .login-subtitle {
                        font-size: 14px;
                        color: #8fb8d8;
                    }

                    entry {
                        min-height: 38px;
                    }

                    button {
                        min-height: 40px;
                    }
                )css"
            );

            auto display = Gdk::Display::get_default();

            if ( display )
            {
                Gtk::StyleContext::add_provider_for_display(display, m_CssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            }
        }

      private:
        Gtk::Box    m_Root;
        Gtk::Box    m_Card;
        Gtk::Box    m_ButtonBox;
        Gtk::Label  m_Title;
        Gtk::Label  m_Subtitle;
        Gtk::Entry  m_UserEntry;
        Gtk::Entry  m_PasswordEntry;
        Gtk::Button m_LoginButton;

        std::function<void()>               m_OnLoginSuccess;
        std::unique_ptr<Gtk::MessageDialog> m_ErrorDialog;
        Glib::RefPtr<Gtk::CssProvider>      m_CssProvider;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
