# CONTRIBUTING.md

## Branch Configuration

### Core Branches

* Our repository maintains three core branches: `main`, `develop`, and `legacy`.
  * `main`: Maintains the latest version of models (*.xml) with completed simulation work and their results (*.xtr). Simulation traces may not always be present.
  * `develop`: Maintains working models that are under active development.
  * `legacy`: Archives work completed before May 15, 2025. Modifications to this branch should be avoided.

### Working Branches

* All working branches should be created from the `develop` branch.
* Naming conventions:
  * `feature/model-*`: For model modifications
  * `feature/sim-*`: For simulation-related work
  * `fix/model-*`: For model bug fixes
  * `chore/*`: For miscellaneous tasks
* Before merging a working branch into `develop`, all previous simulation traces must be removed.

### Main Branch Management

* Before merging into `main`, update and commit the metadata information (metadata.json) in the `develop` branch.
* Version tagging (e.g., `v1.0.0`) is mandatory when merging to `main`.

### Simulation Results Files

* All simulation results should be stored in the respective model's `results` folder.

---

# 브랜치 관리 정책

## 브랜치 구성

### 기본 브랜치

* 레포지토리는 `main`, `develop`, `legacy` 세 가지 기본 브랜치를 유지합니다.
  * `main`: 시뮬레이션 작업이 완료된 최신 버전의 모델(*.xml)과 시뮬레이션 결과(*.xtr)를 유지합니다. 시뮬레이션 트레이스가 존재하지 않을 수 있습니다.
  * `develop`: 작동하는 개발 중인 모델을 유지합니다.
  * `legacy`: 2025년 5월 15일 이전의 작업물을 보관하는 브랜치입니다. 이 브랜치의 수정은 지양합니다.

### 작업 브랜치

* 모든 작업 브랜치는 `develop` 브랜치에서 생성해야 합니다.
* 네이밍 컨벤션:
  * `feature/model-*`: 모델 수정 작업
  * `feature/sim-*`: 시뮬레이션 관련 작업
  * `fix/model-*`: 모델 버그 수정 작업
  * `chore/*`: 기타 작업
* `develop` 브랜치에 작업 브랜치를 머지하기 전 이전 시뮬레이션 트레이스는 삭제해야 합니다.

### Main 브랜치 관리

* `main` 브랜치로 머지하기 전 `develop` 브랜치에서 메타데이터(metadata.json) 정보를 수정 후 커밋해야 합니다.
* `main` 브랜치 머지 시 반드시 버전 태그(예: `v1.0.0`)를 생성해야 합니다.

### 시뮬레이션 결과 파일 규칙

* 모든 시뮬레이션 결과는 각 모델의 `results` 폴더에 저장해야 합니다.