#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(long long startingCoins, QWidget *parent)
    : QMainWindow(parent), player_(startingCoins)
{
    buildUi();
    refreshAll();
}

void MainWindow::buildUi()
{
    setWindowTitle("Mini Project - Andrew Saifnoorian");

    auto central = new QWidget(this);
    auto root = new QVBoxLayout(central);

    auto statusRow = new QHBoxLayout();
    handNameLbl_ = new QLabel("—");
    betLbl_ = new QLabel("Bet: 1");
    payoutLbl_ = new QLabel("Payout: —");

    auto spacer1 = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    statusRow->addWidget(handNameLbl_);
    statusRow->addSpacerItem(spacer1);
    statusRow->addWidget(betLbl_);
    statusRow->addSpacing(20);
    statusRow->addWidget(payoutLbl_);
    root->addLayout(statusRow);
    cardsReadoutLbl_ = new QLabel;
    cardsReadoutLbl_->setAlignment(Qt::AlignLeft);
    cardsReadoutLbl_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    cardsReadoutLbl_->setStyleSheet("font: 14px 'Consolas'; color:#888;");
    root->addWidget(cardsReadoutLbl_);

    auto cardsRow = new QHBoxLayout();
    for (int i = 0; i < 5; ++i)
    {
        auto col = new QVBoxLayout();

        auto card = new QLabel("?");
        card->setAlignment(Qt::AlignCenter);
        card->setMinimumSize(88, 120);
        card->setFrameShape(QFrame::Box);
        card->setStyleSheet("background:#ffffff; border:1px solid #888;");
        card->setTextFormat(Qt::RichText);
        cardLbl_[i] = card;

        auto hold = new QPushButton("Hold");
        hold->setCheckable(true);
        holdBtn_[i] = hold;

        auto stateLbl = new QLabel("Discard");
        stateLbl->setAlignment(Qt::AlignCenter);
        stateLbl->setStyleSheet("color:#666;");
        holdStateLbl_[i] = stateLbl;

        col->addWidget(card);
        col->addSpacing(6);
        col->addWidget(hold);
        col->addWidget(stateLbl);
        cardsRow->addLayout(col);
    }
    root->addLayout(cardsRow);

    auto actionRow = new QHBoxLayout();

    auto betBox = new QGroupBox("Place Your Bet");
    auto betLay = new QHBoxLayout(betBox);
    betGroup_ = new QButtonGroup(this);
    for (int b = 1; b <= 5; ++b)
    {
        auto btn = new QPushButton(QString::number(b));
        btn->setCheckable(true);
        if (b == 1)
            btn->setChecked(true);
        betGroup_->addButton(btn, b);
        betLay->addWidget(btn);
    }
    betGroup_->setExclusive(true);
    connect(betGroup_, &QButtonGroup::idClicked, this, &MainWindow::onBetClicked);

    dealBtn_ = new QPushButton("Deal");
    cashOutBtn_ = new QPushButton("Cash Out");

    actionRow->addWidget(betBox);
    actionRow->addSpacing(20);
    actionRow->addWidget(dealBtn_);
    actionRow->addWidget(cashOutBtn_);
    actionRow->addStretch();

    auto insertLay = new QHBoxLayout();
    insertLay->addWidget(new QLabel("Coins Remaining:"));
    bankrollLbl_ = new QLabel("0");
    bankrollLbl_->setMinimumWidth(80);
    insertLay->addWidget(bankrollLbl_);
    insertLay->addSpacing(20);
    insertLay->addWidget(new QLabel("Insert Coins:"));
    insertSpin_ = new QSpinBox();
    insertSpin_->setRange(0, 1000000);
    insertBtn_ = new QPushButton("Insert");
    insertLay->addWidget(insertSpin_);
    insertLay->addWidget(insertBtn_);
    insertLay->addStretch();

    root->addLayout(actionRow);
    root->addSpacing(8);
    root->addLayout(insertLay);

    setCentralWidget(central);

    connect(dealBtn_, &QPushButton::clicked, this, &MainWindow::onDeal);
    connect(cashOutBtn_, &QPushButton::clicked, this, &MainWindow::onCashOut);
    connect(insertBtn_, &QPushButton::clicked, this, &MainWindow::onInsertCoins);

    connect(holdBtn_[0], &QPushButton::clicked, this, &MainWindow::onToggleHold0);
    connect(holdBtn_[1], &QPushButton::clicked, this, &MainWindow::onToggleHold1);
    connect(holdBtn_[2], &QPushButton::clicked, this, &MainWindow::onToggleHold2);
    connect(holdBtn_[3], &QPushButton::clicked, this, &MainWindow::onToggleHold3);
    connect(holdBtn_[4], &QPushButton::clicked, this, &MainWindow::onToggleHold4);

    setPhase(Phase::Ready);
}

void MainWindow::onBetClicked(int bet)
{
    currentBet_ = bet;
    betLbl_->setText(QString("Bet: %1").arg(bet));
}

void MainWindow::onInsertCoins()
{
    long long v = insertSpin_->value();
    if (v > 0)
        player_.addCoins(v);
    insertSpin_->setValue(0);
    refreshAll();
}

void MainWindow::onCashOut()
{
    QMessageBox::information(this, "Cash Out",
                             QString("You cashed out with %1 coins.").arg(player_.bankroll()));
    qApp->quit();
}

void MainWindow::onToggleHold0() { setHold(0, holdBtn_[0]->isChecked()); }
void MainWindow::onToggleHold1() { setHold(1, holdBtn_[1]->isChecked()); }
void MainWindow::onToggleHold2() { setHold(2, holdBtn_[2]->isChecked()); }
void MainWindow::onToggleHold3() { setHold(3, holdBtn_[3]->isChecked()); }
void MainWindow::onToggleHold4() { setHold(4, holdBtn_[4]->isChecked()); }

void MainWindow::setHold(int idx, bool on)
{
    holds_[idx] = on;
    holdStateLbl_[idx]->setText(on ? "Hold" : "Discard");
}

void MainWindow::resetHolds()
{
    for (int i = 0; i < 5; ++i)
    {
        holds_[i] = false;
        holdBtn_[i]->setChecked(false);
        holdStateLbl_[i]->setText("Discard");
    }
}

static inline QString suitColor(Suit s)
{
    switch (s)
    {
    case Suit::Hearts:
    case Suit::Diamonds:
        return "#C00000";
    case Suit::Clubs:
    case Suit::Spades:
        return "#000000";
    }
    return "#000";
}

static inline QChar suitGlyph(Suit s)
{
    switch (s)
    {
    case Suit::Hearts:
        return QChar(0x2665);
    case Suit::Diamonds:
        return QChar(0x2666);
    case Suit::Clubs:
        return QChar(0x2663);
    case Suit::Spades:
        return QChar(0x2660);
    }
    return '?';
}

QString MainWindow::cardCode(const Card &c) const
{
    // e.g., "10♠" or "Q♥"
    return QString("%1%2")
        .arg(QString::fromStdString(c.rankStr()),
             QString(suitGlyph(c.suit)));
}

void MainWindow::updateCardsReadout()
{
    if (phase_ == Phase::Ready)
    {
        cardsReadoutLbl_->setText("");
        return;
    }
    QStringList parts;
    for (const auto &c : hand_.cards())
        parts << cardCode(c);
    cardsReadoutLbl_->setText("Dealt: " + parts.join("   "));
}

QString MainWindow::cardToText(const Card &c)
{
    const QString r = QString::fromStdString(c.rankStr());
    const QString col = suitColor(c.suit);
    const QChar sym = suitGlyph(c.suit);
    return QString("<div style='font-size:28px; font-weight:600; color:%1'>%2%3</div>")
        .arg(col, r, QString(sym));
}

void MainWindow::refreshCards()
{
    for (int i = 0; i < 5; ++i)
        cardLbl_[i]->setText(cardToText(hand_.cards()[i]));
    updateCardsReadout();
}

void MainWindow::refreshStatus(const EvalResult *res, long long betForStatus, long long paid)
{
    bankrollLbl_->setText(QString::number(player_.bankroll()));
    if (res)
    {
        handNameLbl_->setText(QString::fromStdString(res->name));
        betLbl_->setText(QString("Bet: %1").arg(betForStatus));
        payoutLbl_->setText(paid > 0 ? QString("Payout: +%1").arg(paid) : "Payout: —");
    }
    else
    {
        handNameLbl_->setText("—");
        payoutLbl_->setText("Payout: —");
        betLbl_->setText(QString("Bet: %1").arg(currentBet_));
    }
}

void MainWindow::refreshAll()
{
    refreshStatus(nullptr, 0, 0);
    if (phase_ == Phase::Ready)
    {
        for (int i = 0; i < 5; ++i)
            cardLbl_[i]->setText(
                QString("<div style='color:#888; font-size:20px'>Card %1</div>").arg(i + 1));
        cardsReadoutLbl_->setText("");
    }
    else
    {
        refreshCards();
    }
}

void MainWindow::setPhase(Phase p)
{
    phase_ = p;
    const bool canBet = (p == Phase::Ready);
    for (auto *b : betGroup_->buttons())
        b->setEnabled(canBet);
    for (auto *b : holdBtn_)
        b->setEnabled(p == Phase::Dealt);
    dealBtn_->setText(p == Phase::Dealt ? "Draw" : "Deal");
}

void MainWindow::onDeal()
{
    if (phase_ == Phase::Ready)
    {
        if (!player_.canBet(currentBet_))
        {
            QMessageBox::warning(this, "Invalid Bet",
                                 "Bet must be 1–5 and ≤ bankroll.");
            return;
        }
        deck_.shuffle();
        hand_.clear();
        for (int i = 0; i < 5; ++i)
            hand_.add(deck_.deal());
        resetHolds();
        setPhase(Phase::Dealt);
        refreshAll();
        return;
    }

    if (phase_ == Phase::Dealt)
    {
        std::vector<bool> mask(5, false);
        for (int i = 0; i < 5; ++i)
            mask[i] = holds_[i];

        hand_.replaceExceptHolds(mask, deck_);
        refreshCards();

        auto res = HandEvaluator::evaluate(hand_);
        long long payout = res.multiplier * currentBet_;
        if (res.multiplier > 0)
            player_.win(payout);
        else
            player_.lose(currentBet_);

        refreshStatus(&res, currentBet_, payout);

        setPhase(Phase::Drawn);
        dealBtn_->setText("Deal");
        for (auto *b : holdBtn_)
            b->setEnabled(false);
        return;
    }

    if (phase_ == Phase::Drawn)
    {
        setPhase(Phase::Ready);
        refreshAll();
    }
}
