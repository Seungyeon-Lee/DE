# 10주차 (22. 04. 26)
[Notion Link](https://www.notion.so/10-22-04-26-024549576f594cb6b701a4257599764a)

### 조명이 왜 필요한가?

입체감을 주기 위해서 필요하다.

조명을 가상 세계에 진짜로 시뮬레이션 하려면 엄청나게 많은 연산이 필요하다.

따라서 게임에서는 일부만 연산한 간소화된 버전으로 연산한다. 

실시간 런타임 GI를 흉내낸다.

반사 비율을 줄이는 등의 방식으로 사용한다.

베르트 코사인 법칙 (빛이 근사되는 정도를 계산하는 법칙)

기울기 / 반사각에 따라서 각각의 빛을 연산한다.

실제 환경에서 Specular가 보여지지 않아도 있게끔 그려준다.

더 실사에 가깝게 보이기 위해서 고안된 것이다.

하프 람베르트는 실사에 가깝게 만든 것(실사와 비슷하게 만들 기 어렵기 때문에 보정을 한 것이다)

자연광이 없지만 자연광이 있는 것처럼 만든 것이다.

실제로 연산하기에는 컴퓨터에게 연산 양이 너무나 많다.

현실에 가깝다고 해서 더 예쁘게 보인다는 건 아니다.

처음에 초기화할 때 Window부터 초기화한다.

WindowClass : Window가 어떤 모양으로 만들어질 지 정하는 형태

활성화하면 로그가 디테일하게 나온다.

CreateDevice : 실제 하드웨어를 찾아서 어떤 Adapter를 쓸 지 찾아서 사용한다.

만약에 우리가 원하는 사양을 지원하지 않는 그래픽카드라면 소프트웨어를 그래픽카드처럼 사용(가상으로 만들어주는 작업) 한다.

```cpp
md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)
```

fence도 만들어준다.

**MSAA 적용 코드**

```cpp
D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
msQualityLevels.Format = mBackBufferFormat;
msQualityLevels.SampleCount = 4;
msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
msQualityLevels.NumQualityLevels = 0;
ThrowIfFailed(md3dDevice->CheckFeatureSupport(
	D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
	&msQualityLevels,
	sizeof(msQualityLevels)));

m4xMsaaQuality = msQualityLevels.NumQualityLevels;
assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
```

MSAA는 Anti-aliasing을 해결하는 방법 중 가장 쉬운 방법이고 가장 좋은 방법이다. (퀄리티가 좋다 그러나 메모리를 4배나 먹는다.

Command Object는 GPU한테 명령을 전달해줄 수 있어야 한다

List에 DrawTriangle과 같은 명령을 담는다.

최종적으로 GPU에게 List를 보내기 위해 CreateCommanadQueue한테 List를 담고 GPU에 보낸다.

GPU에서는 이러한 명령들을 하나씩 꺼내서 수행한다

### SwapChain (Double Buffering)

Descriptor Heap
리소스 하나 하나가 어떻게 쓰이느냐를 설명할 수 있는 것이 Descriptor. 이러한 Descriptor를 갖고있는 게 Descriptor Heap.

Pipeline을 만들어서 어떻게 그릴 지 GPU에 알려주어야 한다.

Pipeline을 만들 때 먼저 Root Signature를 만든다.

Shader : 어떤 Vertex 형태를 받을지 (Position, Normal 등 인자마다 갖고 있음)을 선언해둔다. 

CreateDefaultBuffer → GPU 자원을 만들어준다

CreateCommittedResource → 처음부터 CPU, GPU를 할당한다. 자주 사용된다.

만들었던 Shader들은 UploadBuffer에 다 작성해준다.

- Root Signature
- Model
- Material
- RenderItem(책에서 만든 객체. Rendering할 때 쓰이는 모든 변수들을 모아 놓고 있는 것)
- Frame Resource : GPU가 일하는 동안 CPU도 일할 수 있게 하는 기법

Application

- Init
- Update
- Draw

물체만 업데이트되는 것이 아니라 키보드, 카메라의 움직임도 계산해야 한다.

UpdateObjectCBs : 변경된 점을 GPU에 알려주는 함수 

DX12는 CommandList에 무언가를 담기 전에 Allocator를 Reset해주고 다시 메모리를 세팅해주고 CommandList를 작성해줘야 한다. 화면이 어떻게 생겼는지 Viewport를 알려주어야 한다.

Shader를 보면서 Lighting에 관한 것을 알려주어야 한다.

UpdateSubResources<1>
템플릿에 1을 넣는다 ⇒ 개수가 몇개인가

### Light를 GPU에서 어떻게 구현하는가?

라이트를 표현하는 것은 GPU이다.

GPU에서 연산을 해주는 것이다.

GPU에서는 픽셀 하나하나에 대해서 연산해주기 때문이다. 우리가 어떤 색을 표현할 지 알려주는 것이다.

아래의 정보가 shader에서 정해진다.

- Material (색상, 반사도 등)
- Position
- Normal

Vertex Shader에서는 월드 공간의 동차좌표계로 변환시킨다.

다 된 Vertex Buffer를 넘기면 삼각형으로 넘긴 것이지만 보간해서 Rasterizer가 받아서 픽셀 하나하나로 만들어준다.

Up-Vector(Normal)을 바탕으로 카메라 방향에 따라서 달라진다.

### Ligihting Utils

ComputingLighting : Shader의 Light 개수는 정해져 있다.

최대 16개밖에 못쓴다. (해결을 위해 Deferred가 나옴)

물체 재질, 위치, Normal, 카메라 뱡향이 있으면 light를 구할 수 있다.

기울기에 따른 수치가 나오고, Blinn Phong에 넘겨준다.

속도는 Directional이 제일 빠르고 Point 그 다음이 Spot이다.

그림자 표시 때도 속도는 동일한 순서이다.

이유는 Directional은 방향이 하나라서 그림자도 한 방향이기 때문이다.

보통 게임에서는 Direcitonal 하나만 처리하거나, 메인 캐릭터만 처리한다던지 최적화를 해야 한다.

포인트는 매우 느리기 때문에 보통 그림자 처리를 하지 않는다.