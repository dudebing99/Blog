package main

import (
	"fmt"
	"sort"
)

type ContentScore struct {
	ContentID int64
	Score     float32
}

type ContentScoreList []ContentScore

func (cs ContentScoreList) Len() int {
	return len(cs)
}

func (cs ContentScoreList) Swap(i, j int) {
	cs[i], cs[j] = cs[j], cs[i]
}

// 按照 score 逆序排序
func (cs ContentScoreList) Less(i, j int) bool {
	return cs[j].Score < cs[i].Score
}

func main() {
	contentScoreList := ContentScoreList{
		{100, 12.34},
		{200, 9.35},
		{99, 7.90},
		{400, 8.91},
	}

	fmt.Println("按照 score 逆序排序")
	sort.Sort(ContentScoreList(contentScoreList))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}

	fmt.Println("按照 score 升序排序")
	sort.Sort(sort.Reverse((ContentScoreList(contentScoreList))))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}
}
