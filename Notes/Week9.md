# 9주차 (22. 03. 02)
[Notion Link](https://www.notion.so/9-22-03-02-9aaa8760f84d4dc2be9f4a2df7f5a537)

## Frame Resource

CPU, GPU 둘 다 사용한다. 병렬로 돌아간다.

CPU는 명령을 계속 쓰고 GPU는 그 명령을 받아서 처리를 한다.

CPU / GPU를 동시에 활용하는 게 제일 효율이 좋다.

동기화 기법을 사용하다 보면 어쩔 수 없이 한쪽이 쉬는 상황이 발생한다.

이를 해결하기 위해 Frame Resource란 개념이 나타났다.

해당 프레임을 그리는데 필요한 Resource들을 Frame 별로 여러 개 미리 만들어두는 것이다.

책의 구조체를 사용하는 방식은 다음과 같다.

그 프레임에 사용될 Constant Buffer, Command Buffer 등이 있다.

CPU에 프레임 3개를 미리 만들어두고, GPU에 넘기고 CPU는 다른 자원으로 다음을 만들어서 넘기는 것이다. 메모리를 3개나 미리 만든다는 단점은 있지만 대부분의 엔진에서 최적화가 된다.

물론 이게 완벽한 해법은 아니다.

CPU가 훨씬 빠르거나 GPU가 훨씬 빠른 것처럼 속도에 따라서 한쪽이 노는 현상은 여전히 일어난다.

둘의 속도 차이에 따라서 배분을 잘해야 최대한 효율적일 수 있다.

LandAndWaves 예제

Landscape (지형) Height Map이라는 Texture를 이용해서 표현한다.

### Lighting

재질Material을 나타내기 위해서 Lighting을 사용한다. Material은 그래픽스에서 많이 쓰는 용어. 어떤 물체에 대한 정보를 모두 갖고 있는 것을 Material이라고 한다.

Forward Rendering의 가장 큰 단점은 개수를 정해두어야 한다는 것이다.

→ 물체 하나 그릴 때 적용되는 그래픽스 기술을 전부 다 처리한다.

그러나 Deferred에서는 이 부분을 다 나눠 두었기 때문에 개수를 정하지 않고 생성되어야 한다. Forward도 그림자는 따로 처리한다.

## 예제

init이 종류가 여러 개이다.

init은 ContantBuffer인지 Descriptor인지에 따라서 나누어서 할 수 있다.

cpp에도 똑같은 메모리 구조를 가진 Frame Resource를 선언해주고 실행해준다.

Shader마다 Root Signature 설정. (큰 Shader에 많이 등록해두면 다른 Shader를 사용하지 않아도 상관없기 때문에 Uniform Shader를 만들어두고 비용을 아끼기도 한다)

DX12에서는 해당 비용이 많이 줄어서 그냥 써도 상관 없다.

RenderItems : 그리기 위해 필요한 것들을 미리 세팅한다. 프레임마다 필요한 리소스들 (최적화 기법)

Pipeline State가 만들어지고 이걸로 Shader를 사용할 수 있게 된다.

Fence : Frame Resource를 다 쓰고 나중에 Frame Resource를 만들 때까지 waiting하는 것. CPU가 CommandList를 다 작성하고 그 바로 다음에 Fence를 하나 호출해준다. CommandList를 다 작성하고 나선 Fence를 수행하려 할 때 CPU가 CommandList 작성이 끝났음을 알 수 있다.

Fence가 끝나기 전까지는 WaitForSignal 상태로 다음 라인으로 움직이지 않는다.

움직임이 어떻게 바뀌었는지 매 Tick 바꿔준다.

Viewport, ScissorRect 설정

Resource Barrier→ GPU에서 병렬로 처리하기 위해서 필요한 방식

그 전에 그려졌던 것들이 나오면 되지 않기 때문에 Clear해준다.

다시 바뀔 수도 있기 때문에 Root Signature를 또 따로 등록해준다.

타임, 월드뷰, 현재 카메라 위치 등 Shader에 넣어준다.

물체마다 색상을 다르게 하기 위해서 다 GPU로 넘겨준다.

Index Buffer는 선택 사항이지만 메모리 최적화를 위해(정점 개수를 줄여줌) 사용하는 것이 좋다.

HLSL

4바이트로 크기를 다 맞춰주어야 한다.

메모리를 맞춰주지 않으면 CPU와 메모리가 꼬일 수도 있다.

속도가 안 좋아질 수도 있다.

구조체 메모리나 클래스 메모리를 어떻게 정할까?

운영체제에 맞는 메모리에 올라가는 빈 공간을 활용하기 위해서 끼워 넣어서 맞추는 경우가 있었다.

```cpp
struct Text
{
	virtual ~Test();

	int a; // 4byte
	short b; // 2byte
	int c; // 4byte
	char d; // 1byte
};
```

|    4    |  2  |  **2**  |    4    | 1 |   3   | 

가장 큰 메모리로 메모리 공간이 맞춰져서 들어감

중간의 2는 패딩된 것이다.

그래서 예상 메모리는 16이지만 실제로는 24로 나온다.

virtual은 virtual table을 만든다. 즉 포인터를 하나 더 만든다.

(최고 변수 크기가 8바이트라는 뜻)

std::shared_ptr은 ref_counter를 자신이 가지고 있다. 따라서 인자를 넘길 때 직접 shared_ptr로 넘겨야 한다. gc는 ref_count를 주기적으로 검사한다. ref_count가 0이 되면 삭제한다.

weakptr는 ref_count를 올리지 않는다.

Move Semantics : 가진 메모리를 바로 다른 변수에 넘겨주는 것