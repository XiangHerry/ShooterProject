// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)return EBTNodeResult::Failed;
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	AShooterCharacter* AIEnemy = Cast<AShooterCharacter>(AIPawn);
	if (AIEnemy)
	{
		AIEnemy->Fire();
	}
	else
	{
		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::Succeeded;
}
