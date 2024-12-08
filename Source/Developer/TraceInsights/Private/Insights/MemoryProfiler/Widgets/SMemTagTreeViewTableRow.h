// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STreeView.h"

// Insights
#include "Insights/MemoryProfiler/ViewModels/MemTagNodeHelper.h"

class IToolTip;
class SMemCounterTableRowToolTip;

namespace Insights
{
	class FTable;
	class FTableColumn;
}

DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldBeEnabledDelegate, FMemTagNodePtr /*NodePtr*/);
DECLARE_DELEGATE_RetVal_OneParam(bool, FIsColumnVisibleDelegate, const FName /*ColumnId*/);
DECLARE_DELEGATE_RetVal_OneParam(EHorizontalAlignment, FGetColumnOutlineHAlignmentDelegate, const FName /*ColumnId*/);
DECLARE_DELEGATE_ThreeParams(FSetHoveredMemTagTreeViewTableCell, TSharedPtr<Insights::FTable> /*TablePtr*/, TSharedPtr<Insights::FTableColumn> /*ColumnPtr*/, FMemTagNodePtr /*MemTagNodePtr*/);

/** Widget that represents a table row in the tree control. Generates widgets for each column on demand. */
class SMemTagTreeViewTableRow : public SMultiColumnTableRow<FMemTagNodePtr>
{
public:
	SLATE_BEGIN_ARGS(SMemTagTreeViewTableRow) {}
		SLATE_EVENT(FShouldBeEnabledDelegate, OnShouldBeEnabled)
		SLATE_EVENT(FIsColumnVisibleDelegate, OnIsColumnVisible)
		SLATE_EVENT(FGetColumnOutlineHAlignmentDelegate, OnGetColumnOutlineHAlignmentDelegate)
		SLATE_EVENT(FSetHoveredMemTagTreeViewTableCell, OnSetHoveredCell)
		SLATE_ATTRIBUTE(FText, HighlightText)
		SLATE_ATTRIBUTE(FName, HighlightedNodeName)
		SLATE_ARGUMENT(TSharedPtr<Insights::FTable>, TablePtr)
		SLATE_ARGUMENT(FMemTagNodePtr, MemTagNodePtr)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;

	/**
	 * Called when Slate detects that a widget started to be dragged.
	 * Usage:
	 * A widget can ask Slate to detect a drag.
	 * OnMouseDown() reply with FReply::Handled().DetectDrag(SharedThis(this)).
	 * Slate will either send an OnDragDetected() event or do nothing.
	 * If the user releases a mouse button or leaves the widget before
	 * a drag is triggered (maybe user started at the very edge) then no event will be
	 * sent.
	 *
	 * @param  InMyGeometry  Widget geometry
	 * @param  InMouseEvent  MouseMove that triggered the drag
	 *
	 */
	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	TSharedRef<IToolTip> GetRowToolTip() const;
	void InvalidateContent();

protected:
	FSlateColor GetBackgroundColorAndOpacity() const;
	FSlateColor GetBackgroundColorAndOpacity(uint64 Value) const;
	FSlateColor GetOutlineColorAndOpacity() const;
	const FSlateBrush* GetOutlineBrush(const FName ColumnId) const;
	bool HandleShouldBeEnabled() const;
	EVisibility IsColumnVisible(const FName ColumnId) const;
	void OnSetHoveredCell(TSharedPtr<Insights::FTable> InTablePtr, TSharedPtr<Insights::FTableColumn> InColumnPtr, FMemTagNodePtr InMemTagNodePtr);

protected:
	/** A shared pointer to the table view model. */
	TSharedPtr<Insights::FTable> TablePtr;

	/** Data context for this table row. */
	FMemTagNodePtr MemTagNodePtr;

	FShouldBeEnabledDelegate OnShouldBeEnabled;
	FIsColumnVisibleDelegate IsColumnVisibleDelegate;
	FSetHoveredMemTagTreeViewTableCell SetHoveredCellDelegate;
	FGetColumnOutlineHAlignmentDelegate GetColumnOutlineHAlignmentDelegate;

	/** Text to be highlighted on timer name. */
	TAttribute<FText> HighlightText;

	/** Name of the timer node that should be drawn as highlighted. */
	TAttribute<FName> HighlightedNodeName;

	TSharedPtr<SMemCounterTableRowToolTip> RowToolTip;
};
