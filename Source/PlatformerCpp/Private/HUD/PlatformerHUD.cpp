// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlatformerHUD.h"
#include <Controllers/PlatformerController.h>

void APlatformerHUD::CreateStateWidget()
{
	APlayerController* player = GetOwningPlayerController();
	if (stateWidgetClass!=nullptr)
	{
		stateWidget = CreateWidget<UStateWidget>(player, stateWidgetClass);
		stateWidget->AddToViewport();
	}
}

void APlatformerHUD::UpdateCoins(int value)
{
	stateWidget->UpdateCoin(value);
}

void APlatformerHUD::UpdateLife(int value)
{
	stateWidget->UpdateLife(value);
}

void APlatformerHUD::UpdateTime(int value)
{
	stateWidget->UpdateTime(value);
}

void APlatformerHUD::UpdatePoints(int value)
{
	stateWidget->UpdatePoints(value);
}
