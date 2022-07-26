# 10주차 (22. 07. 19)
[Notion Link](https://www.notion.so/10-22-07-19-27e2b848b6794edaa30919a127a3e6f6)

## Model Drawing & Lighting

Depth Stencil은 원래는 1로 지정.

그러나 reversed-z를 사용하기 때문에 0으로 초기화 해주어야 한다.

(Depth 비교 부등호도 반대로 작업해야 함)

Render Command Encoder에서 SetRootSignature 해주기.

Dpeth가 꼬여있어서 모델이 보이지 않을 수 있다.

Deffed Render : 현 세대 렌더링 기법중에 반드시 알아야 한다.

Forward+ Render : Tield forward Rendering과 동일한 방식. 화면을 정사각 크기의 타일로 나눈 뒤, 타일과 겹치는 Light를 기록하고, 현재 타일에 겹치는 Light만을 사용하여 Lighting처리.

move semantic은 const를 붙이면 안된다.

## IK (Inverse Kinematic)

역운동학.

FABRIC (Forward And Backward Reaching Inverse Kinematics)이 평정하고 있음. 앞 뒤로 늘어나는 IK.

### Discriptstor 세팅 비용

GPU로 Upload하기 위해서 개수를 처음에 정해야 하는데, 일정 개수 이상이면 Switching 시켜야 하므로 비용을 줄이기 위해서 적절한 개수로 세팅해주는 것이 중요하다.

Shader SPIR-V (Vulkan)

Z-buffer

### 추가로 해볼 것

- 게임 로직
- 마우스 이벤트 (Window 창 크기 바뀌었을 때 Callback 등록해서 쓸 수 있게)
- Dispatch Queue
- Texture 추가 (RootSignature만 변경하면 됨)

### Render Command Encoder

RenderState 바꿔주는 부분은 최적화를 할 여지가 있다.