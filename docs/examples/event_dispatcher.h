/**
 * \page page-event-dispatcher Event Dispatcher
 *
 * The `event_dispatcher` class is designed to reduce the verbosity and clumsiness of
 * having to check for a bunch of different events in the game loop using a long chain of
 * `if`-statements. The basic idea is to specify the events that we want to "subscribe"
 * to, i.e. the events that we are interested in handling, and let the `event_dispatcher`
 * automatically dispatch the subscribed events whenever they occur. There is no
 * requirement to actually bind a subscribed event to a handler, but it makes little sense
 * not to do so. Handlers can be free functions, member functions or even stateful
 * lambdas, as long as they accept an argument equivalent to `const Event&`, where `Event`
 * is the subscribed event.
 *
 * \code{cpp}
 * #include <centurion.hpp>
 *
 * namespace {
 *
 * // Here we specify that we want to subscribe to four different kinds of events
 * using event_dispatcher = cen::event_dispatcher<cen::quit_event,
 *                                                cen::window_event,
 *                                                cen::keyboard_event,
 *                                                cen::mouse_button_event>;
 *
 * void on_mouse_button_event(const cen::mouse_button_event& event)
 * {
 *   cen::log::info("mouse_button_event");
 * }
 *
 * class Game final
 * {
 *  public:
 *   Game()
 *   {
 *     // Member function handlers
 *     m_dispatcher.bind<cen::quit_event>().to<&Game::on_quit_event>(this);
 *     m_dispatcher.bind<cen::window_event>().to<&Game::on_window_event>(this);
 *
 *     // Lambda handler
 *     m_dispatcher.bind<cen::keyboard_event>().to([](const cen::keyboard_event& event) {
 *       cen::log::info("keyboard_event");
 *     });
 *
 *     // Free function handler
 *     m_dispatcher.bind<cen::mouse_button_event>().to<&on_mouse_button_event>();
 *   }
 *
 *   auto run() -> int
 *   {
 *     m_window.show();
 *
 *     while (m_running)
 *     {
 *       // All we need to do each frame to handle events is to poll the event dispatcher
 *       m_dispatcher.poll();
 *
 *       // More game stuff...
 *     }
 *
 *     m_window.hide();
 *     return 0;
 *   }
 *
 *  private:
 *   cen::window m_window;
 *   event_dispatcher m_dispatcher;
 *   bool m_running{true};
 *
 *   // Invoked for each quit event
 *   void on_quit_event(const cen::quit_event& event)
 *   {
 *     m_running = false;
 *   }
 *
 *   // Invoked for each window event
 *   void on_window_event(const cen::window_event& event)
 *   {
 *     cen::log::info("window_event");
 *   }
 * };
 *
 * }  // namespace
 *
 * int main(int, char**)
 * {
 *   cen::library centurion;
 *
 *   Game game;
 *   return game.run();
 * }
 * \endcode
 */