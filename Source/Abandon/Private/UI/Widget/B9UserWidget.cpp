// Copyright M9Only


#include "UI/Widget/B9UserWidget.h"



void UB9UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
