#include <ComponentSystem/Components/C_Drawable.h>

C_Drawable::C_Drawable()
    : sortOrder(0)
{
}

C_Drawable::~C_Drawable() { }

void C_Drawable::SetSortOrder(int order)
{
    sortOrder = order;
}

int C_Drawable::GetSortOrder() const
{
    return sortOrder;
}
