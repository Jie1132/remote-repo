// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StateWidget.h"

void UStateWidget::UpdateCoin(int value)
{
	FText coins = FText::AsNumber(value);
	coinsNum->SetText(coins);
}

void UStateWidget::UpdateLife(int value)
{
	FText lives = FText::AsNumber(value);
	lifeNum->SetText(lives);
}

void UStateWidget::UpdateTime(int value)
{
	FText curTime = FText::AsNumber(value);
	time->SetText(curTime);
}
void UStateWidget::UpdatePoints(int value)
{
	FText curPoints = FText::AsNumber(value);
	points->SetText(curPoints);
}
