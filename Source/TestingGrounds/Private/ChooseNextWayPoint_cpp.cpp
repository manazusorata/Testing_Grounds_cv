// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWayPoint_cpp.h"
#include"AIController.h"
#include"PatrolingGuard.h"
#include"BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UChooseNextWayPoint_cpp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO Protect empty patrol point

	//Get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast< APatrolingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Set next way Point
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	//UE_LOG(LogTemp, Warning, TEXT("index:%i"), index);
	BlackBoardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[index]);

	//Cycle the index
	auto NextIndex = (index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}