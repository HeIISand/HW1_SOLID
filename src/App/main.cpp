#include "../Logic/MainInventoryCenter.h"
#include "../Logic/MainServiceCenter.h"
#include "ConsoleView.h"
#include "App.h"

#include "../../include/di.h"
#include <memory>

namespace di = boost::di;

int main() {
    const auto injector = di::make_injector(
        di::bind<IServiceCenter>.to<MainServiceCenter>(),
        di::bind<IInventoryCenter>.to<MainInventoryCenter>(),
        di::bind<IView>.to<StandardConsoleView>()
    );

    auto app = injector.create<App>();

    app.run();

    return 0;
}