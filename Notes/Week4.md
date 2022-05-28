# 4주차 (21. 11. 22)
[Notion Link](https://www.notion.so/4-21-11-22-689b2ab307514e6dae076f122a4b126a)

DirectX API를 사용하여 도형을 그릴 수 있다.

## Vertex, Index Buffer

모델을 그리기 위해서는 삼각형을 만들고 GPU에 넘겨주어야 한다.

그 삼각형을 보관하는 것이 Buffer이다.

Indexing해서 삼각형을 그리려 할 때 Index Buffer를 사용한다.

삼각형 면을 점으로 채우기 위해서 하드웨어가 소프트웨어적으로 내부에서 Rasterizer를 돌게 된다.

**정점 버퍼**Vertex Buffer : GPU가 인지할 수 있도록 API에 맞게 삼각형에 대한 Buffer를 담아준다

정점 정보에는 위치 뿐만 아니라 Normal, Color 정보를 담는다.

### Index Buffer는 왜 사용하는가?

![Screenshot_20211210-105333_Samsung_Notes](https://user-images.githubusercontent.com/26589915/170811139-bbad601d-fd05-4eed-9927-7c971211068f.jpg)

사각형을 그리고 싶을 때 정점을 Numbering하여 겹치는 영역의 정점을 두 번 사용하지 않도록 하기 위해서 사용한다. (EX. 그림의 2, 4번 정점 영역)

**Draw API**

DrawPrimitive → DrawIndexPrimitive (Index Buffer 포함 전송)

상황에 따라 다르게 보낼 수 있다.

중첩 인덱스 상황에서 Index Buffer를 쓰면 유리하다.

그러나 중첩되는 경우가 너무 없을 때에는 중첩되는 정점에 사용되는 메모리보다 Index Buffer를 사용하는 메모리가 더 필요한 경우도 존재할 수 있다.

DirectX12에서 물체 → 정적 (움직이지 않음, EX.나무)인 오브젝트에는 자원 할당 방식이 다르다.

static한 경우 GPU에 올리고 변경되지 않기 때문에 CPU에 가지 않고 GPU default heap에 넣는다.

그러나 CPU에서는 바로 GPU deault heap에 접근할 수 없으므로 CPU쪽에는 업로드 목적의 리소스를 만들어서 사용한다. 사용이 완료된 업로드 용 리소스는 해제한다.

## Constant Buffer

Shader에서 사용될 상수(EX. 데이터, 조명 위치, 텍스처 등)를 갖고 있는 Buffer.

리소스는 자주 바뀌기 때문에 주로 UPLOAD 타입을 많이 사용한다.

요구 조건 : 256 바이트의 배수여야 한다. (하드웨어의 최소 할당크기가 256 바이트의 배수이기 때문)

## Blob

리소스는 GPU 자원, Blob은 CPU 자원.

Blob은 일종의 Buffer라고 보면 된다. 어떠한 리소스의 바이트 정보가 담겨있다.

## Shader

GPU에서 해석할 수 있는 어셈블리 (EX. hlsl (DX), glsl …)

그래픽 카드가 일할 수 있도록 해준다.

## Root Signature

Rendering Pipeline에 리소스들이 어떻게 바인딩 될 지를 정의한다.

Root Signature는 Shader에서 어떠한 변수를 사용할 지를 알고 있다.

Compute Shader : 연산을 하는 Shader (보통 Blur 처리를 많이 한다)

최적화는 CPU / GPU 둘 중 어느 곳에서 연산 할 거냐의 차이에 따라 달라진다.

CPU에서 GPU에 메모리를 넘길 때의 오버헤드가 있기 때문이다.

### Semantic

Vertex Buffer에 여러 가지(Position, Normal, Color 등)를 채울 때, Rasterize (정점 사이사이의 픽셀을 채워주는 일)할 때 보간을 하기 위해 명시적으로 써준다.

Input (Vertex CPU → GPU)

Output (Vertex → Pixcel)

Shader 문법은 일반 C++과 다르다. Shader는 Technical Artist들이 주로 작업한다.

프로그래머는 Shader를 사용할 수 있게 제공하는 역할을 한다.

Semantic은 의도를 표현하는 역할.

Shader에서 if는 가능한 사용하지 않는 것이 좋다.

## Pipeline State

DirectX12부터는 Row Graphics, 즉 직접 Pipeline을 수정할 수 있게 되었다. 
(DX11까지는 무조건 Input Asembly)

Pipeline에 대해서 정의한다.

Pipeline이란 하나의 Draw를 하기 위해 필요한 모든 공정이다.

(Input Asembly부터 Output까지)

Blendmode, Stencil Buffer 사용 여부, Render Target 지정 등 모든 것을 정의해주어야 한다.

Shader마다 Pipeline State를 다 정의해주어야 한다.

최대한 Pipeline을 바꾸지 않는 것이 좋다.

Shader에 맞는 Pipeline을 여러 개로 준비해줘야 한다.

**SPIR-V**

Shader를 분석해준다.

Vertex Buffer는 어떻게 들어가 있고 Texture는 어떻게 되어있는지 알아낼 수 있다.

Reflection을 써서, 텍스트 파일로 저장해두는 등 Pipeline을 만든다. (Baked Shader - Runtime에서 가져다 쓴다.)

## **PBR**(Physically Based **Rendering**)

이전에는 Material, Bump-map 등을 직접 제작하여 사용했는데 반사와 같은 계산 자체를 알아서 해준다.

실제 물리학 기반의 재질을 사용한다.

예전에는 최적화 + 현실처럼 보이도록 만들었으나 실제 물리 기반으로 현실처럼 제작한다.

아티스트들이 보기에 이전 방식보다 예쁘게 나오지 않아서 결국엔 이전처럼 돌아가는 일이 일어난다. 미세면 반사에 대한 걸 계산하므로 사실 이 방식도 유사 값을 사용하는 것이다.

**GI (Global Illumination)** : 광원 외의 다른 물체에서 서로 반사되어 영향 받는 조명.

루멘으로 GI와 Reflection을 만들기도 한다.

(루멘은 대부분 PC에서 사용하고 모바일에서는 성능 때문에 잘 사용하지 않는다)

### 최적화

**Frame Resource**

CPU가 명령 날리고 GPU가 일하는 동안 CPU는 아무 일도 하지 않는다.

따라서 CPU를 일하게 하기 위해 똑같은 리소스를 여러 개를 준비해서 프레임마다 그릴 것들을 준비해놓는다. CPU와 GPU를 쉬지 않고 일하게 만들자. (최적화)

**Render Item**

책에서 만든 개념. Rendering을 할 때, Pipeline Render Signatrue가 최대한 바뀌지 않게 하기 위해서, 해당 Signature가 동일한 것들을 묶어 놓은 것. 같은 것들을 함께 그리도록 하기 위해 묶어 놓은 구조체 (EX. Static Mesh)

**Constant Buffer**

상수 버퍼는 여러 종류가 있다. (5 Tick 마다 바뀌는 Buffer… 등)

0번 Register는 자주 바뀌는 것.

1번 Register는 자주 안 바뀌는 것. 등을 그룹으로 나누어서 비용을 줄여서 최적화하는 것.

**Instancing**

Draw Call: 1 Draw를 요청하는 Call.

GPU에 그려 달라고 명령을 내리는 것(이런 명령이 많을수록 느려진다) 같은 모델일 때 (색상, 위치 등등만 다른 경우) 조금 다른 정보들만 따로 배열로 두어 한 번에 GPU에 전달하는 방식.