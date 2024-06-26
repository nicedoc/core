
SHAPESX_DIR = $$PWD/..

!build_single_objects {
SOURCES += $$PWD/pptx_shapes.cpp
}
else {
SOURCES += \
	$$SHAPESX_DIR/CAccentBorderCallout1.cpp \
	$$SHAPESX_DIR/CAccentBorderCallout2.cpp \
	$$SHAPESX_DIR/CAccentBorderCallout3.cpp \
	$$SHAPESX_DIR/CAccentCallout1.cpp \
	$$SHAPESX_DIR/CAccentCallout2.cpp \
	$$SHAPESX_DIR/CAccentCallout3.cpp \
	$$SHAPESX_DIR/CActionButtonBackPrevious.cpp \
	$$SHAPESX_DIR/CActionButtonBeginning.cpp \
	$$SHAPESX_DIR/CActionButtonBlank.cpp \
	$$SHAPESX_DIR/CActionButtonDocument.cpp \
	$$SHAPESX_DIR/CActionButtonEnd.cpp \
	$$SHAPESX_DIR/CActionButtonForwardNext.cpp \
	$$SHAPESX_DIR/CActionButtonHelp.cpp \
	$$SHAPESX_DIR/CActionButtonHome.cpp \
	$$SHAPESX_DIR/CActionButtonInformation.cpp \
	$$SHAPESX_DIR/CActionButtonMovie.cpp \
	$$SHAPESX_DIR/CActionButtonReturn.cpp \
	$$SHAPESX_DIR/CActionButtonSound.cpp \
	$$SHAPESX_DIR/CArc.cpp \
	$$SHAPESX_DIR/CBentArrow.cpp \
	$$SHAPESX_DIR/CBentConnector2.cpp \
	$$SHAPESX_DIR/CBentConnector3.cpp \
	$$SHAPESX_DIR/CBentConnector4.cpp \
	$$SHAPESX_DIR/CBentConnector5.cpp \
	$$SHAPESX_DIR/CBentUpArrow.cpp \
	$$SHAPESX_DIR/CBevel.cpp \
	$$SHAPESX_DIR/CBlockArc.cpp \
	$$SHAPESX_DIR/CBorderCallout1.cpp \
	$$SHAPESX_DIR/CBorderCallout2.cpp \
	$$SHAPESX_DIR/CBorderCallout3.cpp \
	$$SHAPESX_DIR/CBracePair.cpp \
	$$SHAPESX_DIR/CBracketPair.cpp \
	$$SHAPESX_DIR/CCallout1.cpp \
	$$SHAPESX_DIR/CCallout2.cpp \
	$$SHAPESX_DIR/CCallout3.cpp \
	$$SHAPESX_DIR/CCan.cpp \
	$$SHAPESX_DIR/CChartPlus.cpp \
	$$SHAPESX_DIR/CChartStar.cpp \
	$$SHAPESX_DIR/CChartX.cpp \
	$$SHAPESX_DIR/CChevron.cpp \
	$$SHAPESX_DIR/CChord.cpp \
	$$SHAPESX_DIR/CCircularArrow.cpp \
	$$SHAPESX_DIR/CCloud.cpp \
	$$SHAPESX_DIR/CCloudCallout.cpp \
	$$SHAPESX_DIR/CCorner.cpp \
	$$SHAPESX_DIR/CCornerTabs.cpp \
	$$SHAPESX_DIR/CCube.cpp \
	$$SHAPESX_DIR/CCurvedConnector2.cpp \
	$$SHAPESX_DIR/CCurvedConnector3.cpp \
	$$SHAPESX_DIR/CCurvedConnector4.cpp \
	$$SHAPESX_DIR/CCurvedConnector5.cpp \
	$$SHAPESX_DIR/CCurvedDownArrow.cpp \
	$$SHAPESX_DIR/CCurvedLeftArrow.cpp \
	$$SHAPESX_DIR/CCurvedRightArrow.cpp \
	$$SHAPESX_DIR/CCurvedUpArrow.cpp \
	$$SHAPESX_DIR/CDecagon.cpp \
	$$SHAPESX_DIR/CDiagStripe.cpp \
	$$SHAPESX_DIR/CDiamond.cpp \
	$$SHAPESX_DIR/CDodecagon.cpp \
	$$SHAPESX_DIR/CDonut.cpp \
	$$SHAPESX_DIR/CDoubleWave.cpp \
	$$SHAPESX_DIR/CDownArrow.cpp \
	$$SHAPESX_DIR/CDownArrowCallout.cpp \
	$$SHAPESX_DIR/CEllipse.cpp \
	$$SHAPESX_DIR/CEllipseRibbon.cpp \
	$$SHAPESX_DIR/CEllipseRibbon2.cpp \
	$$SHAPESX_DIR/CFlowChartAlternateProcess.cpp \
	$$SHAPESX_DIR/CFlowChartCollate.cpp \
	$$SHAPESX_DIR/CFlowChartConnector.cpp \
	$$SHAPESX_DIR/CFlowChartDecision.cpp \
	$$SHAPESX_DIR/CFlowChartDelay.cpp \
	$$SHAPESX_DIR/CFlowChartDisplay.cpp \
	$$SHAPESX_DIR/CFlowChartDocument.cpp \
	$$SHAPESX_DIR/CFlowChartExtract.cpp \
	$$SHAPESX_DIR/CFlowChartInputOutput.cpp \
	$$SHAPESX_DIR/CFlowChartInternalStorage.cpp \
	$$SHAPESX_DIR/CFlowChartMagneticDisk.cpp \
	$$SHAPESX_DIR/CFlowChartMagneticDrum.cpp \
	$$SHAPESX_DIR/CFlowChartMagneticTape.cpp \
	$$SHAPESX_DIR/CFlowChartManualInput.cpp \
	$$SHAPESX_DIR/CFlowChartManualOperation.cpp \
	$$SHAPESX_DIR/CFlowChartMerge.cpp \
	$$SHAPESX_DIR/CFlowChartMultidocument.cpp \
	$$SHAPESX_DIR/CFlowChartOfflineStorage.cpp \
	$$SHAPESX_DIR/CFlowChartOffpageConnector.cpp \
	$$SHAPESX_DIR/CFlowChartOnlineStorage.cpp \
	$$SHAPESX_DIR/CFlowChartOr.cpp \
	$$SHAPESX_DIR/CFlowChartPredefinedProcess.cpp \
	$$SHAPESX_DIR/CFlowChartPreparation.cpp \
	$$SHAPESX_DIR/CFlowChartProcess.cpp \
	$$SHAPESX_DIR/CFlowChartPunchedCard.cpp \
	$$SHAPESX_DIR/CFlowChartPunchedTape.cpp \
	$$SHAPESX_DIR/CFlowChartSort.cpp \
	$$SHAPESX_DIR/CFlowChartSummingJunction.cpp \
	$$SHAPESX_DIR/CFlowChartTerminator.cpp \
	$$SHAPESX_DIR/CFoldedCorner.cpp \
	$$SHAPESX_DIR/CFrame.cpp \
	$$SHAPESX_DIR/CFunnel.cpp \
	$$SHAPESX_DIR/CGear6.cpp \
	$$SHAPESX_DIR/CGear9.cpp \
	$$SHAPESX_DIR/CHalfFrame.cpp \
	$$SHAPESX_DIR/CHeart.cpp \
	$$SHAPESX_DIR/CHeptagon.cpp \
	$$SHAPESX_DIR/CHexagon.cpp \
	$$SHAPESX_DIR/CHomePlate.cpp \
	$$SHAPESX_DIR/CHorizontalScroll.cpp \
	$$SHAPESX_DIR/CIrregularSeal1.cpp \
	$$SHAPESX_DIR/CIrregularSeal2.cpp \
	$$SHAPESX_DIR/CLeftArrow.cpp \
	$$SHAPESX_DIR/CLeftArrowCallout.cpp \
	$$SHAPESX_DIR/CLeftBrace.cpp \
	$$SHAPESX_DIR/CLeftBracket.cpp \
	$$SHAPESX_DIR/CLeftCircularArrow.cpp \
	$$SHAPESX_DIR/CLeftRightArrow.cpp \
	$$SHAPESX_DIR/CLeftRightArrowCallout.cpp \
	$$SHAPESX_DIR/CLeftRightCircularArrow.cpp \
	$$SHAPESX_DIR/CLeftRightRibbon.cpp \
	$$SHAPESX_DIR/CLeftRightUpArrow.cpp \
	$$SHAPESX_DIR/CLeftUpArrow.cpp \
	$$SHAPESX_DIR/CLightningBolt.cpp \
	$$SHAPESX_DIR/CLine.cpp \
	$$SHAPESX_DIR/CLineInv.cpp \
	$$SHAPESX_DIR/CMathDivide.cpp \
	$$SHAPESX_DIR/CMathEqual.cpp \
	$$SHAPESX_DIR/CMathMinus.cpp \
	$$SHAPESX_DIR/CMathMultiply.cpp \
	$$SHAPESX_DIR/CMathNotEqual.cpp \
	$$SHAPESX_DIR/CMathPlus.cpp \
	$$SHAPESX_DIR/CMoon.cpp \
	$$SHAPESX_DIR/CNonIsoscelesTrapezoid.cpp \
	$$SHAPESX_DIR/CNoSmoking.cpp \
	$$SHAPESX_DIR/CNotchedRightArrow.cpp \
	$$SHAPESX_DIR/COctagon.cpp \
	$$SHAPESX_DIR/CParallelogram.cpp \
	$$SHAPESX_DIR/CPentagon.cpp \
	$$SHAPESX_DIR/CPie.cpp \
	$$SHAPESX_DIR/CPieWedge.cpp \
	$$SHAPESX_DIR/CPlaque.cpp \
	$$SHAPESX_DIR/CPlaqueTabs.cpp \
	$$SHAPESX_DIR/CPlus.cpp \
	$$SHAPESX_DIR/CQuadArrow.cpp \
	$$SHAPESX_DIR/CQuadArrowCallout.cpp \
	$$SHAPESX_DIR/CRect.cpp \
	$$SHAPESX_DIR/CRibbon.cpp \
	$$SHAPESX_DIR/CRibbon2.cpp \
	$$SHAPESX_DIR/CRightArrow.cpp \
	$$SHAPESX_DIR/CRightArrowCallout.cpp \
	$$SHAPESX_DIR/CRightBrace.cpp \
	$$SHAPESX_DIR/CRightBracket.cpp \
	$$SHAPESX_DIR/CRound1Rect.cpp \
	$$SHAPESX_DIR/CRound2DiagRect.cpp \
	$$SHAPESX_DIR/CRound2SameRect.cpp \
	$$SHAPESX_DIR/CRoundRect.cpp \
	$$SHAPESX_DIR/CRtTriangle.cpp \
	$$SHAPESX_DIR/CSmileyFace.cpp \
	$$SHAPESX_DIR/CSnip1Rect.cpp \
	$$SHAPESX_DIR/CSnip2DiagRect.cpp \
	$$SHAPESX_DIR/CSnip2SameRect.cpp \
	$$SHAPESX_DIR/CSnipRoundRect.cpp \
	$$SHAPESX_DIR/CSquareTabs.cpp \
	$$SHAPESX_DIR/CStar10.cpp \
	$$SHAPESX_DIR/CStar12.cpp \
	$$SHAPESX_DIR/CStar16.cpp \
	$$SHAPESX_DIR/CStar24.cpp \
	$$SHAPESX_DIR/CStar32.cpp \
	$$SHAPESX_DIR/CStar4.cpp \
	$$SHAPESX_DIR/CStar5.cpp \
	$$SHAPESX_DIR/CStar6.cpp \
	$$SHAPESX_DIR/CStar7.cpp \
	$$SHAPESX_DIR/CStar8.cpp \
	$$SHAPESX_DIR/CStraightConnector1.cpp \
	$$SHAPESX_DIR/CStripedRightArrow.cpp \
	$$SHAPESX_DIR/CSun.cpp \
	$$SHAPESX_DIR/CSwooshArrow.cpp \
	$$SHAPESX_DIR/CTeardrop.cpp \
	$$SHAPESX_DIR/CTextArchDown.cpp \
	$$SHAPESX_DIR/CTextArchDownPour.cpp \
	$$SHAPESX_DIR/CTextArchUp.cpp \
	$$SHAPESX_DIR/CTextArchUpPour.cpp \
	$$SHAPESX_DIR/CTextButton.cpp \
	$$SHAPESX_DIR/CTextButtonPour.cpp \
	$$SHAPESX_DIR/CTextCanDown.cpp \
	$$SHAPESX_DIR/CTextCanUp.cpp \
	$$SHAPESX_DIR/CTextCascadeDown.cpp \
	$$SHAPESX_DIR/CTextCascadeUp.cpp \
	$$SHAPESX_DIR/CTextChevron.cpp \
	$$SHAPESX_DIR/CTextChevronInverted.cpp \
	$$SHAPESX_DIR/CTextCircle.cpp \
	$$SHAPESX_DIR/CTextCirclePour.cpp \
	$$SHAPESX_DIR/CTextCurveDown.cpp \
	$$SHAPESX_DIR/CTextCurveUp.cpp \
	$$SHAPESX_DIR/CTextDeflate.cpp \
	$$SHAPESX_DIR/CTextDeflateBottom.cpp \
	$$SHAPESX_DIR/CTextDeflateInflate.cpp \
	$$SHAPESX_DIR/CTextDeflateInflateDeflate.cpp \
	$$SHAPESX_DIR/CTextDeflateTop.cpp \
	$$SHAPESX_DIR/CTextDoubleWave1.cpp \
	$$SHAPESX_DIR/CTextFadeDown.cpp \
	$$SHAPESX_DIR/CTextFadeLeft.cpp \
	$$SHAPESX_DIR/CTextFadeRight.cpp \
	$$SHAPESX_DIR/CTextFadeUp.cpp \
	$$SHAPESX_DIR/CTextInflate.cpp \
	$$SHAPESX_DIR/CTextInflateBottom.cpp \
	$$SHAPESX_DIR/CTextInflateTop.cpp \
	$$SHAPESX_DIR/CTextPlain.cpp \
	$$SHAPESX_DIR/CTextRingInside.cpp \
	$$SHAPESX_DIR/CTextRingOutside.cpp \
	$$SHAPESX_DIR/CTextSlantDown.cpp \
	$$SHAPESX_DIR/CTextSlantUp.cpp \
	$$SHAPESX_DIR/CTextStop.cpp \
	$$SHAPESX_DIR/CTextTriangle.cpp \
	$$SHAPESX_DIR/CTextTriangleInverted.cpp \
	$$SHAPESX_DIR/CTextWave1.cpp \
	$$SHAPESX_DIR/CTextWave2.cpp \
	$$SHAPESX_DIR/CTextWave4.cpp \
	$$SHAPESX_DIR/CTrapezoid.cpp \
	$$SHAPESX_DIR/CTriangle.cpp \
	$$SHAPESX_DIR/CUpArrow.cpp \
	$$SHAPESX_DIR/CUpArrowCallout.cpp \
	$$SHAPESX_DIR/CUpDownArrow.cpp \
	$$SHAPESX_DIR/CUpDownArrowCallout.cpp \
	$$SHAPESX_DIR/CUturnArrow.cpp \
	$$SHAPESX_DIR/CVerticalScroll.cpp \
	$$SHAPESX_DIR/CWave.cpp \
	$$SHAPESX_DIR/CWedgeEllipseCallout.cpp \
	$$SHAPESX_DIR/CWedgeRectCallout.cpp \
	$$SHAPESX_DIR/CWedgeRoundRectCallout.cpp
}

HEADERS += \
	$$SHAPESX_DIR/CAccentBorderCallout1.h \
	$$SHAPESX_DIR/CAccentBorderCallout2.h \
	$$SHAPESX_DIR/CAccentBorderCallout3.h \
	$$SHAPESX_DIR/CAccentCallout1.h \
	$$SHAPESX_DIR/CAccentCallout2.h \
	$$SHAPESX_DIR/CAccentCallout3.h \
	$$SHAPESX_DIR/CActionButtonBackPrevious.h \
	$$SHAPESX_DIR/CActionButtonBeginning.h \
	$$SHAPESX_DIR/CActionButtonBlank.h \
	$$SHAPESX_DIR/CActionButtonDocument.h \
	$$SHAPESX_DIR/CActionButtonEnd.h \
	$$SHAPESX_DIR/CActionButtonForwardNext.h \
	$$SHAPESX_DIR/CActionButtonHelp.h \
	$$SHAPESX_DIR/CActionButtonHome.h \
	$$SHAPESX_DIR/CActionButtonInformation.h \
	$$SHAPESX_DIR/CActionButtonMovie.h \
	$$SHAPESX_DIR/CActionButtonReturn.h \
	$$SHAPESX_DIR/CActionButtonSound.h \
	$$SHAPESX_DIR/CArc.h \
	$$SHAPESX_DIR/CBentArrow.h \
	$$SHAPESX_DIR/CBentConnector2.h \
	$$SHAPESX_DIR/CBentConnector3.h \
	$$SHAPESX_DIR/CBentConnector4.h \
	$$SHAPESX_DIR/CBentConnector5.h \
	$$SHAPESX_DIR/CBentUpArrow.h \
	$$SHAPESX_DIR/CBevel.h \
	$$SHAPESX_DIR/CBlockArc.h \
	$$SHAPESX_DIR/CBorderCallout1.h \
	$$SHAPESX_DIR/CBorderCallout2.h \
	$$SHAPESX_DIR/CBorderCallout3.h \
	$$SHAPESX_DIR/CBracePair.h \
	$$SHAPESX_DIR/CBracketPair.h \
	$$SHAPESX_DIR/CCallout1.h \
	$$SHAPESX_DIR/CCallout2.h \
	$$SHAPESX_DIR/CCallout3.h \
	$$SHAPESX_DIR/CCan.h \
	$$SHAPESX_DIR/CChartPlus.h \
	$$SHAPESX_DIR/CChartStar.h \
	$$SHAPESX_DIR/CChartX.h \
	$$SHAPESX_DIR/CChevron.h \
	$$SHAPESX_DIR/CChord.h \
	$$SHAPESX_DIR/CCircularArrow.h \
	$$SHAPESX_DIR/CCloud.h \
	$$SHAPESX_DIR/CCloudCallout.h \
	$$SHAPESX_DIR/CCorner.h \
	$$SHAPESX_DIR/CCornerTabs.h \
	$$SHAPESX_DIR/CCube.h \
	$$SHAPESX_DIR/CCurvedConnector2.h \
	$$SHAPESX_DIR/CCurvedConnector3.h \
	$$SHAPESX_DIR/CCurvedConnector4.h \
	$$SHAPESX_DIR/CCurvedConnector5.h \
	$$SHAPESX_DIR/CCurvedDownArrow.h \
	$$SHAPESX_DIR/CCurvedLeftArrow.h \
	$$SHAPESX_DIR/CCurvedRightArrow.h \
	$$SHAPESX_DIR/CCurvedUpArrow.h \
	$$SHAPESX_DIR/CDecagon.h \
	$$SHAPESX_DIR/CDiagStripe.h \
	$$SHAPESX_DIR/CDiamond.h \
	$$SHAPESX_DIR/CDodecagon.h \
	$$SHAPESX_DIR/CDonut.h \
	$$SHAPESX_DIR/CDoubleWave.h \
	$$SHAPESX_DIR/CDownArrow.h \
	$$SHAPESX_DIR/CDownArrowCallout.h \
	$$SHAPESX_DIR/CEllipse.h \
	$$SHAPESX_DIR/CEllipseRibbon.h \
	$$SHAPESX_DIR/CEllipseRibbon2.h \
	$$SHAPESX_DIR/CFlowChartAlternateProcess.h \
	$$SHAPESX_DIR/CFlowChartCollate.h \
	$$SHAPESX_DIR/CFlowChartConnector.h \
	$$SHAPESX_DIR/CFlowChartDecision.h \
	$$SHAPESX_DIR/CFlowChartDelay.h \
	$$SHAPESX_DIR/CFlowChartDisplay.h \
	$$SHAPESX_DIR/CFlowChartDocument.h \
	$$SHAPESX_DIR/CFlowChartExtract.h \
	$$SHAPESX_DIR/CFlowChartInputOutput.h \
	$$SHAPESX_DIR/CFlowChartInternalStorage.h \
	$$SHAPESX_DIR/CFlowChartMagneticDisk.h \
	$$SHAPESX_DIR/CFlowChartMagneticDrum.h \
	$$SHAPESX_DIR/CFlowChartMagneticTape.h \
	$$SHAPESX_DIR/CFlowChartManualInput.h \
	$$SHAPESX_DIR/CFlowChartManualOperation.h \
	$$SHAPESX_DIR/CFlowChartMerge.h \
	$$SHAPESX_DIR/CFlowChartMultidocument.h \
	$$SHAPESX_DIR/CFlowChartOfflineStorage.h \
	$$SHAPESX_DIR/CFlowChartOffpageConnector.h \
	$$SHAPESX_DIR/CFlowChartOnlineStorage.h \
	$$SHAPESX_DIR/CFlowChartOr.h \
	$$SHAPESX_DIR/CFlowChartPredefinedProcess.h \
	$$SHAPESX_DIR/CFlowChartPreparation.h \
	$$SHAPESX_DIR/CFlowChartProcess.h \
	$$SHAPESX_DIR/CFlowChartPunchedCard.h \
	$$SHAPESX_DIR/CFlowChartPunchedTape.h \
	$$SHAPESX_DIR/CFlowChartSort.h \
	$$SHAPESX_DIR/CFlowChartSummingJunction.h \
	$$SHAPESX_DIR/CFlowChartTerminator.h \
	$$SHAPESX_DIR/CFoldedCorner.h \
	$$SHAPESX_DIR/CFrame.h \
	$$SHAPESX_DIR/CFunnel.h \
	$$SHAPESX_DIR/CGear6.h \
	$$SHAPESX_DIR/CGear9.h \
	$$SHAPESX_DIR/CHalfFrame.h \
	$$SHAPESX_DIR/CHeart.h \
	$$SHAPESX_DIR/CHeptagon.h \
	$$SHAPESX_DIR/CHexagon.h \
	$$SHAPESX_DIR/CHomePlate.h \
	$$SHAPESX_DIR/CHorizontalScroll.h \
	$$SHAPESX_DIR/CIrregularSeal1.h \
	$$SHAPESX_DIR/CIrregularSeal2.h \
	$$SHAPESX_DIR/CLeftArrow.h \
	$$SHAPESX_DIR/CLeftArrowCallout.h \
	$$SHAPESX_DIR/CLeftBrace.h \
	$$SHAPESX_DIR/CLeftBracket.h \
	$$SHAPESX_DIR/CLeftCircularArrow.h \
	$$SHAPESX_DIR/CLeftRightArrow.h \
	$$SHAPESX_DIR/CLeftRightArrowCallout.h \
	$$SHAPESX_DIR/CLeftRightCircularArrow.h \
	$$SHAPESX_DIR/CLeftRightRibbon.h \
	$$SHAPESX_DIR/CLeftRightUpArrow.h \
	$$SHAPESX_DIR/CLeftUpArrow.h \
	$$SHAPESX_DIR/CLightningBolt.h \
	$$SHAPESX_DIR/CLine.h \
	$$SHAPESX_DIR/CLineInv.h \
	$$SHAPESX_DIR/CMathDivide.h \
	$$SHAPESX_DIR/CMathEqual.h \
	$$SHAPESX_DIR/CMathMinus.h \
	$$SHAPESX_DIR/CMathMultiply.h \
	$$SHAPESX_DIR/CMathNotEqual.h \
	$$SHAPESX_DIR/CMathPlus.h \
	$$SHAPESX_DIR/CMoon.h \
	$$SHAPESX_DIR/CNonIsoscelesTrapezoid.h \
	$$SHAPESX_DIR/CNoSmoking.h \
	$$SHAPESX_DIR/CNotchedRightArrow.h \
	$$SHAPESX_DIR/COctagon.h \
	$$SHAPESX_DIR/CParallelogram.h \
	$$SHAPESX_DIR/CPentagon.h \
	$$SHAPESX_DIR/CPie.h \
	$$SHAPESX_DIR/CPieWedge.h \
	$$SHAPESX_DIR/CPlaque.h \
	$$SHAPESX_DIR/CPlaqueTabs.h \
	$$SHAPESX_DIR/CPlus.h \
	$$SHAPESX_DIR/CQuadArrow.h \
	$$SHAPESX_DIR/CQuadArrowCallout.h \
	$$SHAPESX_DIR/CRect.h \
	$$SHAPESX_DIR/CRibbon.h \
	$$SHAPESX_DIR/CRibbon2.h \
	$$SHAPESX_DIR/CRightArrow.h \
	$$SHAPESX_DIR/CRightArrowCallout.h \
	$$SHAPESX_DIR/CRightBrace.h \
	$$SHAPESX_DIR/CRightBracket.h \
	$$SHAPESX_DIR/CRound1Rect.h \
	$$SHAPESX_DIR/CRound2DiagRect.h \
	$$SHAPESX_DIR/CRound2SameRect.h \
	$$SHAPESX_DIR/CRoundRect.h \
	$$SHAPESX_DIR/CRtTriangle.h \
	$$SHAPESX_DIR/CSmileyFace.h \
	$$SHAPESX_DIR/CSnip1Rect.h \
	$$SHAPESX_DIR/CSnip2DiagRect.h \
	$$SHAPESX_DIR/CSnip2SameRect.h \
	$$SHAPESX_DIR/CSnipRoundRect.h \
	$$SHAPESX_DIR/CSquareTabs.h \
	$$SHAPESX_DIR/CStar10.h \
	$$SHAPESX_DIR/CStar12.h \
	$$SHAPESX_DIR/CStar16.h \
	$$SHAPESX_DIR/CStar24.h \
	$$SHAPESX_DIR/CStar32.h \
	$$SHAPESX_DIR/CStar4.h \
	$$SHAPESX_DIR/CStar5.h \
	$$SHAPESX_DIR/CStar6.h \
	$$SHAPESX_DIR/CStar7.h \
	$$SHAPESX_DIR/CStar8.h \
	$$SHAPESX_DIR/CStraightConnector1.h \
	$$SHAPESX_DIR/CStripedRightArrow.h \
	$$SHAPESX_DIR/CSun.h \
	$$SHAPESX_DIR/CSwooshArrow.h \
	$$SHAPESX_DIR/CTeardrop.h \
	$$SHAPESX_DIR/CTextArchDown.h \
	$$SHAPESX_DIR/CTextArchDownPour.h \
	$$SHAPESX_DIR/CTextArchUp.h \
	$$SHAPESX_DIR/CTextArchUpPour.h \
	$$SHAPESX_DIR/CTextButton.h \
	$$SHAPESX_DIR/CTextButtonPour.h \
	$$SHAPESX_DIR/CTextCanDown.h \
	$$SHAPESX_DIR/CTextCanUp.h \
	$$SHAPESX_DIR/CTextCascadeDown.h \
	$$SHAPESX_DIR/CTextCascadeUp.h \
	$$SHAPESX_DIR/CTextChevron.h \
	$$SHAPESX_DIR/CTextChevronInverted.h \
	$$SHAPESX_DIR/CTextCircle.h \
	$$SHAPESX_DIR/CTextCirclePour.h \
	$$SHAPESX_DIR/CTextCurveDown.h \
	$$SHAPESX_DIR/CTextCurveUp.h \
	$$SHAPESX_DIR/CTextDeflate.h \
	$$SHAPESX_DIR/CTextDeflateBottom.h \
	$$SHAPESX_DIR/CTextDeflateInflate.h \
	$$SHAPESX_DIR/CTextDeflateInflateDeflate.h \
	$$SHAPESX_DIR/CTextDeflateTop.h \
	$$SHAPESX_DIR/CTextDoubleWave1.h \
	$$SHAPESX_DIR/CTextFadeDown.h \
	$$SHAPESX_DIR/CTextFadeLeft.h \
	$$SHAPESX_DIR/CTextFadeRight.h \
	$$SHAPESX_DIR/CTextFadeUp.h \
	$$SHAPESX_DIR/CTextInflate.h \
	$$SHAPESX_DIR/CTextInflateBottom.h \
	$$SHAPESX_DIR/CTextInflateTop.h \
	$$SHAPESX_DIR/CTextPlain.h \
	$$SHAPESX_DIR/CTextRingInside.h \
	$$SHAPESX_DIR/CTextRingOutside.h \
	$$SHAPESX_DIR/CTextSlantDown.h \
	$$SHAPESX_DIR/CTextSlantUp.h \
	$$SHAPESX_DIR/CTextStop.h \
	$$SHAPESX_DIR/CTextTriangle.h \
	$$SHAPESX_DIR/CTextTriangleInverted.h \
	$$SHAPESX_DIR/CTextWave1.h \
	$$SHAPESX_DIR/CTextWave2.h \
	$$SHAPESX_DIR/CTextWave4.h \
	$$SHAPESX_DIR/CTrapezoid.h \
	$$SHAPESX_DIR/CTriangle.h \
	$$SHAPESX_DIR/CUpArrow.h \
	$$SHAPESX_DIR/CUpArrowCallout.h \
	$$SHAPESX_DIR/CUpDownArrow.h \
	$$SHAPESX_DIR/CUpDownArrowCallout.h \
	$$SHAPESX_DIR/CUturnArrow.h \
	$$SHAPESX_DIR/CVerticalScroll.h \
	$$SHAPESX_DIR/CWave.h \
	$$SHAPESX_DIR/CWedgeEllipseCallout.h \
	$$SHAPESX_DIR/CWedgeRectCallout.h \
	$$SHAPESX_DIR/CWedgeRoundRectCallout.h
