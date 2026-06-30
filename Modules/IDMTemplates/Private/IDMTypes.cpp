#include "IDMTypes.h"
#include "IDMPathRouter.h"

    void IDMTemplates::TableRoute::RegisterRoute() const 
    {
        DatabaseRouterImpl::RegisterRoute(
            std::string(Path),
            std::string(Database),
            std::string(TableName),
            columns,
            columnCount,
            ForCollection
        );
    }




