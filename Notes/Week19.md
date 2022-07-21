# 9주차 (22. 07. 05)
[Notion Link](https://www.notion.so/9-22-07-05-e76c1720469c41efa787eab5fabbd6d0)

## Forward Rendering

Lighting * Model 개수 (Lighting을 한정적으로 사용)

→ Light에 영향을 받지 않아도 빛을 연산. 화면에 렌더링 되지 않는 면도 Shading 연산.

Lighting이 여러 개인 상황에서 관리가 어려움. (한정적으로 사용해야 함.)

## Deferred Rendering

Lighting + Model 개수

→ 배치가 간단하고 엔진에서 관리가 쉽다.

수많은 작은 동적 Lighting 사용이 가능하다. Lighting 계산을 먼저 하지 않고 미루었다 진행하므로 지연 Shading이라 부른다.

**Fov (Field of view)** : 화각

## tiny loader

.obj 파일을 로드하는 라이브러리.