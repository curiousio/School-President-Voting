//
//  voting.c
//  School-President-Voting
//
//  Created by Sam Kim on 19/11/2018.
//  Copyright ⓒ 2018 Sam Kim. All rights reserved.
//

#include <stdio.h>		// 표준 입출력 함수
#include <string.h>     // 문자열을 다루는 함수
#include <Windows.h>	// Sleep(ms) -> 시간 지연 함수

int main()
{
	int CADIDATE_NUM = 0;			// 후보자 수, 처음에는 0 이지만 파일에서 읽은 세트로 업데이트
	char president[100][101];		// 회장 이름, 최대 100명 이름 100글자
	char vice_president[100][101];	// 부회장 이름, 최대 100명
	char promise[100][201];			// 공약, 최대 100명
	unsigned long len;
	int i;
	int mode;
	int exit_caution;
	int count[100] = { 0, };		// 후보별 투표 수
	int num_select;
	int voted_person;
	int keepoff;
	int max = -1;					// 최대 득표 수
	int maxindex = 0;				// 최대 득표 후보자
	int maxcount = 0;				// 최대 득표 후보자의 수

	FILE *candidatefile;			// 후보자 정보 읽기
	FILE *outfile;					// 결과 파일 쓰기

	candidatefile = fopen("candidate.txt", "r");		// 파일이 없으면 0이
	if (candidatefile == 0)
	{
		printf("\t** CAUTION! ** 후보자 정보 파일이 없습니다. 후보자 정보 파일이 있는지 확인 후 다시 시도하십시오.\n\n");
		printf("\t프로그램을 실행할 수 없습니다. 프로그램을 종료합니다.\n\n");
		return -1;
	}

	// fscanf는 공백이 있는 경우 공백은 읽을 수 없음
	for (i = 0; fgets(president[i], 101, candidatefile) != 0; i++)		// fgets의 결과가 0 이면 더 이상 파일에서 읽을 내용이 없음
	{
		len = strlen(president[i]);		// fgets는 \n도 읽어오기 때문에 \n자리에 \0를 넣어서 \n를 삭제함
		president[i][len - 1] = '\0';	// hello를 읽으면, h e l l o \n \0로 읽힘

		fgets(vice_president[i], 101, candidatefile);
		len = strlen(vice_president[i]);
		vice_president[i][len - 1] = '\0';

		fgets(promise[i], 201, candidatefile);
		len = strlen(promise[i]);
		promise[i][len - 1] = '\0';
	}
	CADIDATE_NUM = i;

	while (1)		// 무한 반복, if -> break로 탈출
	{
		printf("★♥★♥★♥★♥★♥★♥★♥★♥★♥★♥★\n");
		printf("\n");
		printf("\t1. 후보자 정보 보기\n");
		printf("\t2. 투표하기\n");
		printf("\t3. 결과보기\n");
		printf("\t4. 결과 저장하기\n");
		printf("\t9. 도움말\n");
		printf("\t0. 종료하기\n");
		printf("\n");
		printf("★♥★♥★♥★♥★♥★♥★♥★♥★♥★♥★\n");


		printf("\n\n작업 선택(원하는 작업의 숫자를 입력 후에 'ENTER' 키를 누르세요.): ");
		scanf("%d", &mode);
		printf("\n");


		if (mode == 1)		// 후보자 정보 보기
		{
			system("cls");

			for (i = 0; i < CADIDATE_NUM; i++)
			{
				printf("기호 %d번 후보자 정보\n\n", i + 1);
				printf("회장 후보: %s\n", president[i]);
				printf("부회장 후보: %s\n", vice_president[i]);
				printf("공약: %s\n", promise[i]);
				printf("\n\n");
			}

			system("pause");
			printf("\n");
		}
		else if (mode == 2)		// 투표 하기
		{
			system("cls");

			for (i = 0; i < CADIDATE_NUM; i++)		// 득표 수 초기화
			{
				count[i] = 0;
			}

			printf("\t투표에 참여하는 인원 수를 입력하십시오.\n");
			printf("\t인원: ");
			scanf("%d", &voted_person);
			printf("\n");


			while (voted_person > 0)		// 투표자가 더 이상 없을 때 까지
			{
				for (i = 0; i < CADIDATE_NUM; i++)		// 후보 보여주기
				{
					printf("기호 %d번 후보자 정보\n\n", i + 1);
					printf("회장 후보: %s\n", president[i]);
					printf("부회장 후보: %s\n", vice_president[i]);
					printf("공약: %s\n", promise[i]);
					printf("\n\n");
				}

				printf("어떤 후보를 선택하시겠습니까?\n");
				scanf("%d", &num_select);
				count[num_select - 1]++;		//  해당 후보자, 득표 수 올리기
				voted_person -= 1;

				// for Visual Studio
				system("cls");		// 투표 비밀 유지를 위해 화면 지움

				// for XCode
				/*
				for (keepoff = 0; keepoff < 100; keepoff++)
				{
					printf("\n");
				}
				*/
			}

			printf("\t** 모든 인원이 투표를 완료하였습니다. **\n\n");

			// 최대 득표자 찾음
			max = -1;
			maxindex = 0;
			maxcount = 0;
			for (i = 0; i < CADIDATE_NUM; i++)
			{
				if (count[i] > max)
				{
					max = count[i];
					maxindex = i;
				}
			}
			// 중복된 최다 득표자 찾음
			for (i = 0; i < CADIDATE_NUM; i++)
			{
				if (count[i] == max)
				{
					maxcount++;
				}
			}

			system("pause");
			printf("\n");
		}
		else if (mode == 3)		// 결과 보기
		{
			system("cls");

			printf("결과를 공개합니다!\n\n");

			for (num_select = 1; num_select <= CADIDATE_NUM; num_select++)
			{
				printf("\t기호 %d번: %d\n", num_select, count[num_select - 1]);
			}
			printf("\n");

			// 중복된 최대 득표자 찾음
			if (maxcount != 1)
			{
				printf("\t** CAUTION! ** 유일한 당선자가 없으므로 투표를 다시 진행해야 합니다. 2번을 선택하여 다시 투표하십시오.\n\n");
			}
			else	// 중복된 최대 득표자가 없을 경우
			{
				printf("축하합니다. %d번 후보가 %d명의 선택으로 당선되었습니다!\n\n", maxindex + 1, max); // 투표하기(2번)에서 구한 maxindex에 1을 더해 출력(배열은 0부터 후보는 1부터 시작하기 때문)
			}

			system("pause");
			printf("\n");
		}
		else if (mode == 4)		// 파일로 저장하기
		{
			system("cls");

			outfile = fopen("result.txt", "w");
			if (candidatefile == 0)
			{
				printf("\t** CAUTION! ** 파일을 생성할 수 없습니다.\n");
				return -1;
			}

			// 모든 후보자 득표 파일로 쓰기
			for (i = 0; i < CADIDATE_NUM; i++)
			{
				fprintf(outfile, "기호 %d번\n", i + 1);
				fprintf(outfile, "회장 후보: %s\n", president[i]);
				fprintf(outfile, "부회장 후보: %s\n", vice_president[i]);
				fprintf(outfile, "공약: %s\n\n", promise[i]);
				fprintf(outfile, "득표 수: %d표\n\n\n\n", count[i]);
			}

			if (maxcount != 1)
			{
				fprintf(outfile, "\t** CAUTION! ** 유일한 당선자가 없으므로 투표를 다시 진행해야 합니다.\n\n");
			}
			else	// 중복된 최대 득표자가 없을 경우
			{
				fprintf(outfile, "%d번 후보가 %d명의 선택으로 당선되었습니다.\n\n", maxindex + 1, max);	// 최대 득표자 파일로 쓰기
			}

			fclose(outfile);

			printf("\t** 저장이 성공적으로 완료되었습니다. **\n\n");

			system("pause");
			printf("\n");
		}
		else if (mode == 9)		// 도움말 출력
		{
			system("cls");

			printf("\t** 도움말 **\n\n");
			printf("\t프로그램의 기능을 설명합니다.\n\n");
			printf("\t'1.'은 후보자의 이름, 공약이 적힌 설명을 제공합니다.\n");
			printf("\t'2.'은 후보자를 골라서 투표를 진행합니다.\n");
			printf("\t'3.'은 투표 결과를 발표합니다.\n");
			printf("\t'4.'은 투표 결과를 파일로 저장합니다.\n");
			printf("\t'0.'은 투표 프로그램을 종료합니다.\n\n");

			system("pause");
			printf("\n");
		}
		else if (mode == 0)		// 종료하기
		{
			system("cls");

			printf("\t종료 이전에 저장하지 않으면 모든 결과가 사라지니 주의하십시오.\n");
			printf("\t투표가 끝나고 저장을 하지 않았다면 이 화면의 바로 이전 단계에서 4번을 선택하여 결과를 저장하십시오.\n");
			printf("\t계속 진행하려면 '2018'을 정확하게 입력하십시오.\n");
			printf("\n정말 진행 하시겠습니까? _ ");
			scanf("%d", &exit_caution);


			if (exit_caution == 2018)		// 한 번 더 확인
			{
				printf("\n\t** 수고하셨습니다. **\n\n");
				printf("\t프로그램을 종료합니다.\n\n");
				printf("Copyright ⓒ 2018 Sam Kim. All rights reserved.\n\n");
				system("pause");
				break;
			}
			else
			{
				printf("\n\t** CAUTION! ** 투표 결과를 저장한 후 다시 시도 하십시오.\n\n");
			}
		}
	}

	fclose(candidatefile);		// 파일 close

	return 0;
}
