#pragma once
#include <QMainWindow>
#include <array>
#include <vector>
#include <memory>

#include "../include/deck.h"
#include "../include/hand.h"
#include "../include/player.h"
#include "../include/evaluator.h"

class QLabel;
class QPushButton;
class QButtonGroup;
class QSpinBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(long long startingCoins, QWidget *parent = nullptr);

private slots:
    void onDeal();
    void onCashOut();
    void onBetClicked(int bet);
    void onInsertCoins();

    void onToggleHold0();
    void onToggleHold1();
    void onToggleHold2();
    void onToggleHold3();
    void onToggleHold4();

private:
    enum class Phase
    {
        Ready,
        Dealt,
        Drawn
    };

    std::array<QLabel *, 5> cardLbl_{};
    std::array<QPushButton *, 5> holdBtn_{};
    std::array<QLabel *, 5> holdStateLbl_{};
    QPushButton *dealBtn_{};
    QPushButton *cashOutBtn_{};
    QButtonGroup *betGroup_{};
    QLabel *betLbl_{};
    QLabel *handNameLbl_{};
    QLabel *payoutLbl_{};
    QLabel *bankrollLbl_{};
    QLabel *cardsReadoutLbl_{};
    QSpinBox *insertSpin_{};
    QPushButton *insertBtn_{};

    Deck deck_;
    Hand hand_;
    Player player_;
    long long currentBet_{1};
    Phase phase_{Phase::Ready};
    std::array<bool, 5> holds_{false, false, false, false, false};

    void buildUi();
    void refreshAll();
    void refreshCards();
    void refreshStatus(const EvalResult *res = nullptr, long long betForStatus = 0, long long paid = 0);
    void setHold(int idx, bool on);
    void resetHolds();
    void setPhase(Phase p);
    static QString cardToText(const Card &c);

    QString cardCode(const Card &c) const;
    void updateCardsReadout();
};
