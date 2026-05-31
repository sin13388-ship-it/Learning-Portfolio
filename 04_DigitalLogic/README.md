# Digital Logic 筆記 [Home](../README.md#learning-portfolio)

## 說在前面
由於對本課程的基礎概念已有一定程度的掌握，這份學習歷程將著重記錄自主延伸的內容，以及那些讓我多想了一會兒的細節。

## 目錄
1. [MCU的基本架構及運作原理](#mcu的基本架構及運作原理)
2. Arduino 實作

### MCU的基本架構及運作原理
- 什麼是Memory mapping I/O (MMIO)?
    - Memory-Mapped I/O 是一種讓 CPU 透過記憶體位址來存取硬體裝置的機制
    - 當 CPU 對某個映射位址寫入資料，匯流排控制器會識別這個位址不屬於 RAM，而是轉送給對應的硬體裝置。
    - 應用場景
        - 嵌入式系統（GPIO、UART、SPI、I2C 控制器）
        - GPU 顯示緩衝區（Framebuffer）
        - PCIe 裝置的 BAR（Base Address Register）
        - 網路卡的 DMA 描述符
    - 優缺點 :
        **優點**

        - 統一的指令集：不需要特殊 I/O 指令，LOAD/STORE 就夠了
        - 靈活的位址空間：可以映射大量裝置
        - 支援 DMA：裝置可直接與記憶體溝通，不需 CPU 介入每次傳輸

        **缺點**

        - 佔用位址空間：裝置會消耗 CPU 的記憶體位址範圍
        - 快取問題：需特別標記為 non-cacheable，否則 CPU 快取會讓硬體看不到最新值
        - 除錯較難：看起來像普通記憶體操作，容易混淆