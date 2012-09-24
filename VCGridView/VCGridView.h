//
//  VCGridView.h
//  
//
//  Created by Vinay Chavan on 19/03/11.
//  
//  Copyright (C) 2011 by Vinay Chavan
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions: 
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

/*
 * create UIGridViewItem { image or imageUrl }
 * if items go out of the screen, remove subviews representing those items
 * add scroll delegate methods to check which Cells are turning visible or going out of the screen
 * 
 */

#import <UIKit/UIKit.h>

#import "VCGridViewCell.h"

@protocol VCGridViewDataSource;
@protocol VCGridViewDelegate;

@interface VCGridView : UIView <UIScrollViewDelegate> {
@private
    id<VCGridViewDelegate> _delegate;
	id<VCGridViewDataSource> _dataSource;
	
	UIScrollView *_scrollView;

	NSMutableArray *_cells;
	NSUInteger _numberOfCells;
	NSUInteger _numberOfCellsInRow;
	NSUInteger _numberOfRows;
	
	NSRange currentVisibleRange;
	
	CGFloat _cellWidth;
	CGFloat _rowHeight;
	
	NSMutableArray *_reusableCells;
	
	BOOL _isEditing;
	NSMutableIndexSet *_selectedIndexes;
}

@property (nonatomic, assign) id<VCGridViewDelegate> delegate;
@property (nonatomic, assign) id<VCGridViewDataSource> dataSource;
@property (nonatomic, readonly) BOOL isEditing;
@property (nonatomic, readonly) NSIndexSet *selectedIndexes;

- (void)reloadData;
- (VCGridViewCell *)cellAtIndex:(NSUInteger)index;
- (VCGridViewCell *)dequeueReusableCell;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;
- (void)insertCellAtIndex:(NSUInteger)index animated:(BOOL)animated;
- (void)removeCellAtIndex:(NSUInteger)index animated:(BOOL)animated;
@end


@protocol VCGridViewDataSource <NSObject>

@required
- (NSInteger)numberOfCellsInGridView:(VCGridView*)gridView;

@optional
- (NSInteger)numberOfCellsInRowForGridView:(VCGridView *)gridView;
- (VCGridViewCell *)gridView:(VCGridView *)gridView cellAtIndex:(NSInteger)index;
- (BOOL)gridView:(VCGridView *)gridView canEditCellAtIndex:(NSInteger)index;
@end

@protocol VCGridViewDelegate <NSObject>

@optional
- (CGFloat)heightForRowsInGridView:(VCGridView *)gridView;

- (void)gridView:(VCGridView *)gridView didSelectCellAtIndex:(NSInteger)index;

@end