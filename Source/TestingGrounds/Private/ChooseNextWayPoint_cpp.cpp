// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWayPoint_cpp.h"
#include"AIController.h"
#include"PatrolingGuard.h"
#include"Patrol_Route.h"
#include"BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UChooseNextWayPoint_cpp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO Protect against no patorl route component
	

	//Get the patrol route
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrol_Route>();
	if(!ensure(PatrolRoute)) 
	{
		return EBTNodeResult::Failed;
	}

	//Warning about empty patrol point
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing PatrolPoints"));
		return EBTNodeResult::Failed;
	}

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