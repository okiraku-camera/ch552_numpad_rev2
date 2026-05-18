# macro_numpad

English version is here: [README_en.md](README_en.md)

## 概要

macro_numpad は、CH552G をベースにしたプログラマブルなテンキー / マクロキーパッドです。
デフォルトでは通常のテンキーとして動作し、Web UI でキーマップやマクロをカスタマイズできます。

## 主な機能

- デュアルモード: テンキーモードまたはマクロパッドモード（スイッチ0 に割り当てた NumLockまたはFn で制御）
- 2レイヤーのキーマップシステム（Num/Fn 動作）
- 最大10個のマクロ（m0-m9）
- 修飾キー組み合わせ対応（Shift/Ctrl/Alt/Win）
- NVM（内蔵 EEPROM, 128 bytes）への永続保存

## ハードウェア概要

- MCU: CH552G（USB 2.0 Full Speed）
- マトリクス: 4x5 配置
- 実装スイッチ数: 17
- スイッチ0 (NumLockキー) 
- 多機能 LED:
  - テンキーモード: NumLock インジケータ
  - マクロパッドモード: レイヤーインジケータ

## ソフトウェア構成

- ファームウェアスケッチ（このディレクトリ）: `macro_numpad.ino`
- Web UI（リポジトリルート `html/`）: `../html/macro_numpad.html`, `../html/macro_numpad.js`, `../html/style.css`
- 共通 CH552 キーパッド用ソースは Arduino ライブラリ `ch552_keyPad_Library` で提供されます。

## 使い方

### はじめて使うとき

1. パソコンに macro_numpad を接続します。
2. `../html/macro_numpad.html` をブラウザで開きます。
3. 画面の「Connect to Keyboard」を押して、表示されたデバイスを選びます。
4. 画面上のキーをクリックして、好きなキー操作やマクロを割り当てます。
5. 「Write」操作で本体に保存します。

### ふだんの使い方

- スイッチ0にFnキー機能を割り当てている場合、Num キー（スイッチ0）でテンキー動作とマクロ動作を切り替えられます。
- 保存した内容は次回接続時もそのまま使えます。
- マクロ実行中に別のキーを押すと、そのマクロは止まります。

### 困ったとき

- デバイスが見つからない場合は、USB ケーブルの抜き差し後に再接続してください。
- 接続できない場合は、ブラウザを再読み込みして再度「Connect to Keyboard」を実行してください。

### WebUI 詳細ガイド

詳しい画面説明は次を参照してください。

- 日本語: `../html/README.md`
- English: `../html/README_en.md`

## ビルド

このファームウェアは次の環境でビルドできます。

- Visual Studio Code + vscode-arduino 拡張
- arduino-cli
- CH55xDuino v0.25
- ch552_keyPad_Library（Arduino の user libraries ディレクトリ）

### ボード設定

ボード設定メニューで次を選択してください。

- USB Settings: `USER CODE w/ 148B USB ram`

このオプションは、HID エンドポイントに必要な USB RAM を割り当てます。

## 技術メモ

- キーマップとマクロは別々に保存されます。
- マクロ再生中にいずれかのキーが押されると、マクロ送信は即座に中断されます。
- ブートローダ起動時にデバイスが一時的に切断される場合があります。

## ライセンス

このプロジェクトは MIT License の下で公開されています。
