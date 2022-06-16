# 2주차 (22. 05. 10)
[Notion Link](https://www.notion.so/2-22-05-10-edd842360fcf4a4c91ca0472d8d771e9)

### 자료구조 직접 구현

std 써보면서 인터페이스 익혀보고 직접 개선할 수 있을 것 같다 싶을 때 구현해보는 것을 추천.

dll이 있을 때에는 dllexport를 사용해야 한다.

C++의 header는 명세서와 같은 의미를 가진다.

전처리기를 필터링할 때에는 ifdef 사용한다.

실행 파일이 커지지 않는 이유는 메모리를 공유해서 쓰기 때문이다. 여러 프로그램에서 하나의 dll로 메모리를 공유해서 쓸 수 있다. 단점은 dll을 같이 배포해야만 하고, 동적으로 로드하기 때문에 실행타임이 길어진다.

예시로, 멀티플랫폼일 때 그래픽 라이브러리를 교체한다고 한다면 DirectX.dll을 언로드하고 Vulkan.dll을 로드하면 된다. 어플리케이션 실행 도중에도 dll로 교체가 가능하다.

### no-op

아무것도 하지 않는다는 의미. (no operation)

라이브러리는 main을 제공하지 않는다.

플랫폼 별로 구현할 수 있도록 ApplicationContextInterface에서 Context를 사용할 수 있도록 만든다.

현 구현 상황에서 플랫폼 별로 달라지는 건 사실상 Message Loop밖에 없다.

(GetMessageW로 기다렸다가 메시지 넘겨주는 것이 전부)

SetUnhandledExceptionFilter 함수로 앱이 터질 때 어떻게 처리할 것 인지에 대한 필터를 걸 수 있다.

**mini dump** : 프로그램이 살아있을 때 메모리를 Snapshot한 파일

**constexpr** : 컴파일 타임에 계산하게 해 달라는 의미 (C++14)

**noexcept** : 에러를 던지지 않는다.

**final** : virtual 제공 상속 받지 않도록 한다.

## CMake

---

dbuild_shard_libs=yes (dll 사용)

cmake도 같이 써보면 좋다. 프로젝트 세팅 자동화.

### Thirdparty를 제공하는 방법

thirdparty.props에서 자신을 빌드하기 이전에 prebuild하도록 만들 수 있다. (솔루션으로 Thirdparty를 빌드하는 경우)

그러나 Thirdparty를 빌드 하다가 빌드 다되기 전에 자신을 빌드하려고 넘어가버려서 없다고 오류가 나기도 한다. → 폴더로 놓고 관리하자! 참조로 넣고 사용하면 된다.

<aside>
📌 **Thirdparty 쉽게 활용하는 Tip** : cmake로 빌드해보고 세팅을 보고 필요한 것만 가져온다.

</aside>

Interface → Metal Interface 따라서 구현.

```cpp
// init에서 CreateGraphicDevice.
// 순수 가상함수로 init을 만들고 상속받아서 구현하도록 한다.
class GrahphicsDevice
{
		CommandQueue
		RenderPipeLine
		GPUBuffer
}
```

- Allocator
- Buffer
- Encoder
- SwapChain