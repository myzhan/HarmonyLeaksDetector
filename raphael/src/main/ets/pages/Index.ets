import { hilog } from '@kit.PerformanceAnalysisKit';
import raphael from 'libraphael.so';

const MAP64_MODE = 0x00800000;
const ALLOC_MODE = 0x00400000;

@Entry
@Component
struct Index {
  build() {
    Row() {
      Column() {
        Row() {
          Button("Start", { type: ButtonType.Normal, stateEffect: true })
            .borderRadius(4)
            .backgroundColor("#FFEBCD")
            .fontSize(13)
            .fontColor(Color.Black)
            .width(110)
            .height(40)
            .padding({ left: 2, right: 2 })
            .onClick(() => {
              raphael.Start(MAP64_MODE | ALLOC_MODE | 0x0F0000 | 10, "raphael", ".*")
            })
        }
        Row() {
          Button("Malloc", { type: ButtonType.Normal, stateEffect: true })
            .borderRadius(4)
            .backgroundColor("#FFEBCD")
            .fontSize(13)
            .fontColor(Color.Black)
            .width(110)
            .height(40)
            .padding({ left: 2, right: 2 })
            .onClick(() => {
              raphael.Malloc()
            })
        }
        Row() {
          Button("Stop", { type: ButtonType.Normal, stateEffect: true })
            .borderRadius(4)
            .backgroundColor("#FFEBCD")
            .fontSize(13)
            .fontColor(Color.Black)
            .width(110)
            .height(40)
            .padding({ left: 2, right: 2 })
            .onClick(() => {
              raphael.Stop()
            })
        }
        Row() {
          Button("Print", { type: ButtonType.Normal, stateEffect: true })
            .borderRadius(4)
            .backgroundColor("#FFEBCD")
            .fontSize(13)
            .fontColor(Color.Black)
            .width(110)
            .height(40)
            .padding({ left: 2, right: 2 })
            .onClick(() => {
              raphael.Print()
            })
        }
      }
    }
  }
}
